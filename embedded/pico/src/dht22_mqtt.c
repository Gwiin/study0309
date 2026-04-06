#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "pico/unique_id.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "hardware/sync.h"
#include "lwip/apps/mqtt.h"
#include "lwip/apps/mqtt_priv.h"
#include "lwip/altcp_tls.h"
#include "lwip/dns.h"

#ifndef MQTT_SERVER
#error Need to define MQTT_SERVER
#endif

#ifdef MQTT_CERT_INC
#include MQTT_CERT_INC
#endif

#ifndef DHT22_GPIO
#define DHT22_GPIO 15
#endif

#ifndef MQTT_TOPIC_LEN
#define MQTT_TOPIC_LEN 128
#endif

#ifndef MQTT_DEVICE_NAME
#define MQTT_DEVICE_NAME "pico2w-dht22"
#endif

#ifndef MQTT_PUB_TOPIC
#define MQTT_PUB_TOPIC "/node_a/environment"
#endif

#ifndef LCD_I2C
#define LCD_I2C i2c0
#endif

#ifndef LCD_I2C_SDA_PIN
#define LCD_I2C_SDA_PIN 4
#endif

#ifndef LCD_I2C_SCL_PIN
#define LCD_I2C_SCL_PIN 5
#endif

#ifndef LCD_I2C_ADDR
#define LCD_I2C_ADDR 0x27
#endif

#define MQTT_KEEP_ALIVE_S 60
#define MQTT_PUBLISH_QOS 1
#define MQTT_PUBLISH_RETAIN 0
#define DHT22_SAMPLE_INTERVAL_MS 1000
#define DHT22_POWERUP_DELAY_MS 2000
#define LCD_I2C_BAUDRATE 100000

#define LCD_CHARACTER 1
#define LCD_COMMAND 0

#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_FUNCTIONSET 0x20
#define LCD_SETDDRAMADDR 0x80
#define LCD_ENTRYLEFT 0x02
#define LCD_DISPLAYON 0x04
#define LCD_2LINE 0x08
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE_BIT 0x04

typedef struct {
    mqtt_client_t *client;
    struct mqtt_connect_client_info_t info;
    ip_addr_t server_address;
    bool wifi_ready;
    bool dns_requested;
    bool dns_resolved;
    bool mqtt_connected;
    absolute_time_t next_reconnect_attempt;
} APP_STATE_T;

static uint8_t lcd_i2c_addr = LCD_I2C_ADDR;

static void lcd_i2c_write_byte(uint8_t value) {
    i2c_write_blocking(LCD_I2C, lcd_i2c_addr, &value, 1, false);
}

static void lcd_toggle_enable(uint8_t value) {
    sleep_us(600);
    lcd_i2c_write_byte(value | LCD_ENABLE_BIT);
    sleep_us(600);
    lcd_i2c_write_byte(value & (uint8_t)~LCD_ENABLE_BIT);
    sleep_us(600);
}

static void lcd_send_byte(uint8_t value, int mode) {
    uint8_t high = (uint8_t)(mode | (value & 0xF0) | LCD_BACKLIGHT);
    uint8_t low = (uint8_t)(mode | ((value << 4) & 0xF0) | LCD_BACKLIGHT);

    lcd_i2c_write_byte(high);
    lcd_toggle_enable(high);
    lcd_i2c_write_byte(low);
    lcd_toggle_enable(low);
}

static void lcd_clear(void) {
    lcd_send_byte(LCD_CLEARDISPLAY, LCD_COMMAND);
    sleep_ms(2);
}

static void lcd_set_cursor(int line, int position) {
    uint8_t address = (uint8_t)((line == 0 ? 0x80 : 0xC0) + position);
    lcd_send_byte(address, LCD_COMMAND);
}

static void lcd_string(const char *text) {
    while (*text) {
        lcd_send_byte((uint8_t)*text++, LCD_CHARACTER);
    }
}

static void lcd_print_line(int line, const char *text) {
    char buffer[17];
    size_t len = strlen(text);

    memset(buffer, ' ', sizeof(buffer));
    if (len > 16) {
        len = 16;
    }
    memcpy(buffer, text, len);
    buffer[16] = '\0';

    lcd_set_cursor(line, 0);
    lcd_string(buffer);
}

static void lcd_init_display(void) {
    i2c_init(LCD_I2C, LCD_I2C_BAUDRATE);
    gpio_set_function(LCD_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(LCD_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(LCD_I2C_SDA_PIN);
    gpio_pull_up(LCD_I2C_SCL_PIN);

    sleep_ms(50);
    uint8_t dummy;
    int found_addr = -1;
    const int candidate_addrs[] = {LCD_I2C_ADDR, 0x3F, 0x27};

    for (size_t i = 0; i < sizeof(candidate_addrs) / sizeof(candidate_addrs[0]); ++i) {
        int addr = candidate_addrs[i];
        if (addr == found_addr) {
            continue;
        }
        int rc = i2c_read_blocking(LCD_I2C, (uint8_t)addr, &dummy, 1, false);
        if (rc >= 0) {
            found_addr = addr;
            break;
        }
    }

    if (found_addr >= 0) {
        lcd_i2c_addr = (uint8_t)found_addr;
        printf("[LCD] detected I2C addr=0x%02x\n", found_addr);
    } else {
        printf("[LCD] no response at 0x%02x or 0x3f, using 0x%02x\n", LCD_I2C_ADDR, LCD_I2C_ADDR);
    }

    sleep_ms(20);
    lcd_send_byte(0x03, LCD_COMMAND);
    sleep_ms(5);
    lcd_send_byte(0x03, LCD_COMMAND);
    sleep_ms(5);
    lcd_send_byte(0x03, LCD_COMMAND);
    sleep_ms(5);
    lcd_send_byte(0x02, LCD_COMMAND);
    sleep_ms(5);
    lcd_send_byte(LCD_ENTRYMODESET | LCD_ENTRYLEFT, LCD_COMMAND);
    lcd_send_byte(LCD_FUNCTIONSET | LCD_2LINE, LCD_COMMAND);
    lcd_send_byte(LCD_DISPLAYCONTROL | LCD_DISPLAYON, LCD_COMMAND);
    lcd_clear();
}

static void lcd_show_status(const char *line1, const char *line2) {
    lcd_print_line(0, line1);
    lcd_print_line(1, line2);
}

static void lcd_show_measurement(float temperature_c, float humidity_percent) {
    char line1[17];
    char line2[17];

    snprintf(line1, sizeof(line1), "Temp:%5.1f C", temperature_c);
    snprintf(line2, sizeof(line2), "Humi:%5.1f %%", humidity_percent);
    lcd_show_status(line1, line2);
}

static bool wait_for_level_timeout(uint gpio, bool level, uint32_t timeout_us) {
    uint64_t start = time_us_64();
    while (gpio_get(gpio) != level) {
        if ((time_us_64() - start) > timeout_us) {
            return false;
        }
    }
    return true;
}

static void dht22_init(void) {
    gpio_init(DHT22_GPIO);
    gpio_set_dir(DHT22_GPIO, GPIO_IN);
    gpio_pull_up(DHT22_GPIO);
}

static bool dht22_read(float *temperature_c, float *humidity_percent) {
    uint8_t data[5] = {0};
    uint32_t irq_state;

    gpio_set_dir(DHT22_GPIO, GPIO_OUT);
    gpio_put(DHT22_GPIO, 0);
    sleep_ms(2);
    gpio_put(DHT22_GPIO, 1);
    busy_wait_us_32(30);
    gpio_set_dir(DHT22_GPIO, GPIO_IN);
    gpio_pull_up(DHT22_GPIO);

    irq_state = save_and_disable_interrupts();

    if (!wait_for_level_timeout(DHT22_GPIO, 0, 100)) {
        restore_interrupts(irq_state);
        return false;
    }
    if (!wait_for_level_timeout(DHT22_GPIO, 1, 100)) {
        restore_interrupts(irq_state);
        return false;
    }
    if (!wait_for_level_timeout(DHT22_GPIO, 0, 100)) {
        restore_interrupts(irq_state);
        return false;
    }

    for (int i = 0; i < 40; ++i) {
        uint64_t pulse_start;
        uint32_t pulse_width_us;

        if (!wait_for_level_timeout(DHT22_GPIO, 1, 100)) {
            restore_interrupts(irq_state);
            return false;
        }

        pulse_start = time_us_64();
        if (!wait_for_level_timeout(DHT22_GPIO, 0, 100)) {
            restore_interrupts(irq_state);
            return false;
        }
        pulse_width_us = (uint32_t)(time_us_64() - pulse_start);

        data[i / 8] <<= 1;
        if (pulse_width_us > 50) {
            data[i / 8] |= 1;
        }
    }

    restore_interrupts(irq_state);

    if (((uint8_t)(data[0] + data[1] + data[2] + data[3])) != data[4]) {
        return false;
    }

    uint16_t raw_humidity = ((uint16_t)data[0] << 8) | data[1];
    uint16_t raw_temperature = ((uint16_t)(data[2] & 0x7f) << 8) | data[3];

    *humidity_percent = (float)raw_humidity / 10.0f;
    *temperature_c = (float)raw_temperature / 10.0f;
    if (data[2] & 0x80) {
        *temperature_c = -*temperature_c;
    }

    return true;
}

static void pub_request_cb(__unused void *arg, err_t err) {
    if (err != ERR_OK) {
        printf("[MQTT] publish failed: %d\n", err);
    }
}

static void mqtt_connection_cb(__unused mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
    APP_STATE_T *state = (APP_STATE_T *)arg;

    if (status == MQTT_CONNECT_ACCEPTED) {
        state->mqtt_connected = true;
        printf("[MQTT] connected to broker\n");
        lcd_show_status("MQTT connected", "Waiting data...");
        return;
    }

    state->mqtt_connected = false;
    state->dns_resolved = false;
    state->dns_requested = false;
    state->next_reconnect_attempt = make_timeout_time_ms(3000);
    printf("[MQTT] connection closed or failed: %d\n", status);
    lcd_show_status("MQTT failed", "Retrying...");
}

static void start_mqtt(APP_STATE_T *state) {
#if LWIP_ALTCP && LWIP_ALTCP_TLS
    const int port = MQTT_TLS_PORT;
#else
    const int port = MQTT_PORT;
#endif

    if (state->client) {
        mqtt_client_free(state->client);
        state->client = NULL;
    }

    state->client = mqtt_client_new();
    if (!state->client) {
        printf("[MQTT] client allocation failed\n");
        state->next_reconnect_attempt = make_timeout_time_ms(3000);
        lcd_show_status("MQTT alloc err", "Retrying...");
        return;
    }

    printf("[MQTT] connecting to %s\n", ipaddr_ntoa(&state->server_address));

    cyw43_arch_lwip_begin();
    err_t err = mqtt_client_connect(state->client, &state->server_address, port, mqtt_connection_cb, state, &state->info);
#if LWIP_ALTCP && LWIP_ALTCP_TLS
    if (err == ERR_OK) {
        mbedtls_ssl_set_hostname(altcp_tls_context(state->client->conn), MQTT_SERVER);
    }
#endif
    cyw43_arch_lwip_end();

    if (err != ERR_OK) {
        printf("[MQTT] connect request failed: %d\n", err);
        mqtt_client_free(state->client);
        state->client = NULL;
        state->next_reconnect_attempt = make_timeout_time_ms(3000);
        lcd_show_status("MQTT conn err", "Retrying...");
    }
}

static void dns_found(const char *hostname, const ip_addr_t *ipaddr, void *arg) {
    APP_STATE_T *state = (APP_STATE_T *)arg;

    if (!ipaddr) {
        printf("[DNS] failed for %s\n", hostname);
        state->dns_requested = false;
        state->next_reconnect_attempt = make_timeout_time_ms(3000);
        lcd_show_status("DNS failed", "Retrying...");
        return;
    }

    state->server_address = *ipaddr;
    state->dns_resolved = true;
    printf("[DNS] %s -> %s\n", hostname, ipaddr_ntoa(ipaddr));
    start_mqtt(state);
}

static void request_dns(APP_STATE_T *state) {
    cyw43_arch_lwip_begin();
    err_t err = dns_gethostbyname(MQTT_SERVER, &state->server_address, dns_found, state);
    cyw43_arch_lwip_end();

    state->dns_requested = true;

    if (err == ERR_OK) {
        state->dns_resolved = true;
        printf("[DNS] cached -> %s\n", ipaddr_ntoa(&state->server_address));
        start_mqtt(state);
    } else if (err != ERR_INPROGRESS) {
        printf("[DNS] request failed: %d\n", err);
        state->dns_requested = false;
        state->next_reconnect_attempt = make_timeout_time_ms(3000);
        lcd_show_status("DNS req failed", "Retrying...");
    }
}

static bool publish_environment(APP_STATE_T *state, float temperature_c, float humidity_percent) {
    char payload[64];
    err_t err;

    snprintf(payload, sizeof(payload), "temp=%.1f,humidity=%.1f", temperature_c, humidity_percent);

    cyw43_arch_lwip_begin();
    err = mqtt_publish(
        state->client,
        MQTT_PUB_TOPIC,
        payload,
        strlen(payload),
        MQTT_PUBLISH_QOS,
        MQTT_PUBLISH_RETAIN,
        pub_request_cb,
        state
    );
    cyw43_arch_lwip_end();

    if (err != ERR_OK) {
        printf("[MQTT] publish request failed: %d\n", err);
        lcd_show_status("Publish failed", "Check broker");
        return false;
    }

    printf("[PUB] topic=%s payload=%s\n", MQTT_PUB_TOPIC, payload);
    lcd_show_measurement(temperature_c, humidity_percent);
    return true;
}

int main(void) {
    APP_STATE_T state = {0};
    char unique_id[5];
    char client_id[32];
    float temperature_c = 0.0f;
    float humidity_percent = 0.0f;
    absolute_time_t next_sample_time;

    stdio_init_all();
    sleep_ms(2000);
    printf("dht22_mqtt starting\n");

    dht22_init();
    lcd_init_display();
    lcd_show_status("DHT22 MQTT", "Booting...");

    if (cyw43_arch_init()) {
        panic("Failed to initialize CYW43");
    }

    cyw43_arch_enable_sta_mode();
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        panic("Failed to connect to Wi-Fi");
    }

    state.wifi_ready = true;
    printf("[WIFI] connected\n");
    lcd_show_status("WiFi connected", "Resolving MQTT");

    pico_get_unique_board_id_string(unique_id, sizeof(unique_id));
    for (size_t i = 0; i < sizeof(unique_id) - 1; ++i) {
        unique_id[i] = (char)tolower((unsigned char)unique_id[i]);
    }
    snprintf(client_id, sizeof(client_id), "%s-%s", MQTT_DEVICE_NAME, unique_id);

    state.info.client_id = client_id;
    state.info.keep_alive = MQTT_KEEP_ALIVE_S;
#if defined(MQTT_USERNAME) && defined(MQTT_PASSWORD)
    state.info.client_user = MQTT_USERNAME;
    state.info.client_pass = MQTT_PASSWORD;
#else
    state.info.client_user = NULL;
    state.info.client_pass = NULL;
#endif
#if LWIP_ALTCP && LWIP_ALTCP_TLS
#ifdef MQTT_CERT_INC
    static const uint8_t ca_cert[] = TLS_ROOT_CERT;
    static const uint8_t client_key[] = TLS_CLIENT_KEY;
    static const uint8_t client_cert[] = TLS_CLIENT_CERT;
    state.info.tls_config = altcp_tls_create_config_client_2wayauth(
        ca_cert,
        sizeof(ca_cert),
        client_key,
        sizeof(client_key),
        NULL,
        0,
        client_cert,
        sizeof(client_cert)
    );
#else
    state.info.tls_config = altcp_tls_create_config_client(NULL, 0);
#endif
#endif

    printf("[MQTT] client_id=%s\n", client_id);
    printf("[DHT22] gpio=%d\n", DHT22_GPIO);
    printf("[MQTT] publish topic=%s\n", MQTT_PUB_TOPIC);
    printf("[LCD] i2c addr=0x%02x sda=%d scl=%d\n", LCD_I2C_ADDR, LCD_I2C_SDA_PIN, LCD_I2C_SCL_PIN);
    printf("[DHT22] wait %d ms for sensor startup\n", DHT22_POWERUP_DELAY_MS);
    sleep_ms(DHT22_POWERUP_DELAY_MS);

    state.next_reconnect_attempt = get_absolute_time();
    next_sample_time = get_absolute_time();

    while (true) {
        cyw43_arch_poll();

        if (state.wifi_ready &&
            !state.mqtt_connected &&
            !state.dns_requested &&
            absolute_time_diff_us(get_absolute_time(), state.next_reconnect_attempt) <= 0) {
            request_dns(&state);
        }

        if (state.mqtt_connected &&
            absolute_time_diff_us(get_absolute_time(), next_sample_time) <= 0) {
            if (dht22_read(&temperature_c, &humidity_percent)) {
                publish_environment(&state, temperature_c, humidity_percent);
            } else {
                printf("[DHT22] read failed\n");
                lcd_show_status("DHT22 read", "failed");
            }
            next_sample_time = delayed_by_ms(next_sample_time, DHT22_SAMPLE_INTERVAL_MS);
            if (absolute_time_diff_us(get_absolute_time(), next_sample_time) <= 0) {
                next_sample_time = make_timeout_time_ms(DHT22_SAMPLE_INTERVAL_MS);
            }
        }

        cyw43_arch_wait_for_work_until(make_timeout_time_ms(50));
    }

    return 0;
}

