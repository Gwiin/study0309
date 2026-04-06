#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"

// Override with -DBUZZER_GPIO=<gpio> if your buzzer is wired elsewhere.
#ifndef BUZZER_GPIO
#define BUZZER_GPIO 16
#endif

#define NOTE_REST 0
#define NOTE_E5 659
#define NOTE_C5 523
#define NOTE_G5 784
#define NOTE_G4 392
#define NOTE_E4 330
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_AS4 466
#define NOTE_FS5 740
#define NOTE_A5 880
#define NOTE_F5 698
#define NOTE_D5 587
#define NOTE_C6 1046
#define NOTE_C4 262
#define NOTE_GS4 415
#define NOTE_DS5 622

#define T16 75
#define T8  150
#define T4  300
#define T2  600

#define NOTE_GAP_MS 30
#define PWM_WRAP 65535

static uint buzzer_slice;
static uint buzzer_channel;

static void delay_ms_variable(uint16_t duration_ms) {
    sleep_ms(duration_ms);
}

static void buzzer_stop(void) {
    pwm_set_chan_level(buzzer_slice, buzzer_channel, 0);
}

static void buzzer_set_frequency(uint32_t freq) {
    if (freq == NOTE_REST) {
        buzzer_stop();
        return;
    }

    uint32_t system_clock_hz = clock_get_hz(clk_sys);
    float divider = (float)system_clock_hz / ((float)freq * (float)(PWM_WRAP + 1u));

    if (divider < 1.0f) {
        divider = 1.0f;
    } else if (divider > 255.0f) {
        divider = 255.0f;
    }

    pwm_set_clkdiv(buzzer_slice, divider);
    pwm_set_chan_level(buzzer_slice, buzzer_channel, (PWM_WRAP + 1u) / 2u);
}

static void play_note(uint16_t freq, uint16_t duration_ms) {
    if (freq == NOTE_REST) {
        buzzer_stop();
        delay_ms_variable(duration_ms);
        return;
    }

    buzzer_set_frequency(freq);
    delay_ms_variable(duration_ms);
    buzzer_stop();
    delay_ms_variable(NOTE_GAP_MS);
}

static void buzzer_init(void) {
    gpio_set_function(BUZZER_GPIO, GPIO_FUNC_PWM);

    buzzer_slice = pwm_gpio_to_slice_num(BUZZER_GPIO);
    buzzer_channel = pwm_gpio_to_channel(BUZZER_GPIO);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, PWM_WRAP);
    pwm_init(buzzer_slice, &config, true);
    buzzer_stop();
}

int main(void) {
    stdio_init_all();
    buzzer_init();

    while (true) {
        // Super Mario Bros. Overworld Theme ver.gpt

        // 1
        play_note(NOTE_E5, T8);
        play_note(NOTE_REST, T16);
        play_note(NOTE_E5, T8);
        play_note(NOTE_REST, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_REST, T8);

        play_note(NOTE_C5, T8);
        play_note(NOTE_REST, T16);
        play_note(NOTE_E5, T8);
        play_note(NOTE_REST, T8);
        play_note(NOTE_G5, T4);
        play_note(NOTE_REST, T4);
        play_note(NOTE_G4, T4);
        play_note(NOTE_REST, T4);

        // 2
        play_note(NOTE_C5, T4);
        play_note(NOTE_REST, T8);
        play_note(NOTE_G4, T4);
        play_note(NOTE_REST, T8);
        play_note(NOTE_E4, T4);
        play_note(NOTE_REST, T8);

        play_note(NOTE_A4, T8);
        play_note(NOTE_B4, T8);
        play_note(NOTE_AS4, T16);
        play_note(NOTE_A4, T8);
        play_note(NOTE_REST, T16);

        play_note(NOTE_G4, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_G5, T8);
        play_note(NOTE_A5, T4);
        play_note(NOTE_REST, T16);

        play_note(NOTE_F5, T8);
        play_note(NOTE_G5, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_C5, T8);
        play_note(NOTE_D5, T8);
        play_note(NOTE_B4, T4);
        play_note(NOTE_REST, T8);

        // 3
        play_note(NOTE_C5, T4);
        play_note(NOTE_REST, T8);
        play_note(NOTE_G4, T4);
        play_note(NOTE_REST, T8);
        play_note(NOTE_E4, T4);
        play_note(NOTE_REST, T8);

        play_note(NOTE_A4, T8);
        play_note(NOTE_B4, T8);
        play_note(NOTE_AS4, T16);
        play_note(NOTE_A4, T8);
        play_note(NOTE_REST, T16);

        play_note(NOTE_G4, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_G5, T8);
        play_note(NOTE_A5, T4);
        play_note(NOTE_REST, T16);

        play_note(NOTE_F5, T8);
        play_note(NOTE_G5, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_C5, T8);
        play_note(NOTE_D5, T8);
        play_note(NOTE_B4, T4);
        play_note(NOTE_REST, T8);

        // 4
        play_note(NOTE_G5, T16);
        play_note(NOTE_FS5, T16);
        play_note(NOTE_F5, T16);
        play_note(NOTE_D5, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_REST, T16);

        play_note(NOTE_G4, T8);
        play_note(NOTE_A4, T8);
        play_note(NOTE_C5, T4);

        play_note(NOTE_A4, T8);
        play_note(NOTE_C5, T8);
        play_note(NOTE_D5, T4);
        play_note(NOTE_REST, T8);

        play_note(NOTE_G5, T16);
        play_note(NOTE_FS5, T16);
        play_note(NOTE_F5, T16);
        play_note(NOTE_D5, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_REST, T16);

        play_note(NOTE_C6, T8);
        play_note(NOTE_C6, T16);
        play_note(NOTE_C6, T4);
        play_note(NOTE_REST, T8);

        // 5
        play_note(NOTE_G5, T16);
        play_note(NOTE_FS5, T16);
        play_note(NOTE_F5, T16);
        play_note(NOTE_D5, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_REST, T16);

        play_note(NOTE_G4, T8);
        play_note(NOTE_A4, T8);
        play_note(NOTE_C5, T4);

        play_note(NOTE_A4, T8);
        play_note(NOTE_C5, T8);
        play_note(NOTE_D5, T4);
        play_note(NOTE_REST, T8);

        play_note(NOTE_DS5, T8);
        play_note(NOTE_D5, T8);
        play_note(NOTE_C5, T4);
        play_note(NOTE_REST, T4);

        // 6
        play_note(NOTE_C5, T8);
        play_note(NOTE_C5, T16);
        play_note(NOTE_C5, T8);
        play_note(NOTE_REST, T16);

        play_note(NOTE_C5, T8);
        play_note(NOTE_D5, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_C5, T8);
        play_note(NOTE_A4, T8);
        play_note(NOTE_G4, T4);
        play_note(NOTE_REST, T8);

        play_note(NOTE_C5, T8);
        play_note(NOTE_C5, T16);
        play_note(NOTE_C5, T8);
        play_note(NOTE_REST, T16);

        play_note(NOTE_C5, T8);
        play_note(NOTE_D5, T8);
        play_note(NOTE_E5, T4);
        play_note(NOTE_REST, T4);

        // 7
        play_note(NOTE_C5, T8);
        play_note(NOTE_C5, T16);
        play_note(NOTE_C5, T8);
        play_note(NOTE_REST, T16);

        play_note(NOTE_C5, T8);
        play_note(NOTE_D5, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_C5, T8);
        play_note(NOTE_A4, T8);
        play_note(NOTE_G4, T4);
        play_note(NOTE_REST, T8);

        play_note(NOTE_E5, T8);
        play_note(NOTE_REST, T16);
        play_note(NOTE_E5, T8);
        play_note(NOTE_REST, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_REST, T8);

        play_note(NOTE_C5, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_G5, T4);
        play_note(NOTE_G4, T4);
        play_note(NOTE_REST, T4);

        // 8
        play_note(NOTE_C5, T4);
        play_note(NOTE_REST, T8);
        play_note(NOTE_G4, T4);
        play_note(NOTE_REST, T8);
        play_note(NOTE_E4, T4);
        play_note(NOTE_REST, T8);

        play_note(NOTE_A4, T8);
        play_note(NOTE_B4, T8);
        play_note(NOTE_AS4, T16);
        play_note(NOTE_A4, T8);
        play_note(NOTE_REST, T16);

        play_note(NOTE_G4, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_G5, T8);
        play_note(NOTE_A5, T4);
        play_note(NOTE_REST, T16);

        play_note(NOTE_F5, T8);
        play_note(NOTE_G5, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_C5, T8);
        play_note(NOTE_D5, T8);
        play_note(NOTE_B4, T4);
        play_note(NOTE_REST, T8);

        // 9
        play_note(NOTE_E5, T16);
        play_note(NOTE_C5, T16);
        play_note(NOTE_G4, T8);
        play_note(NOTE_REST, T16);

        play_note(NOTE_G4, T8);
        play_note(NOTE_A4, T8);
        play_note(NOTE_F5, T8);
        play_note(NOTE_F5, T16);
        play_note(NOTE_A4, T8);

        play_note(NOTE_B4, T8);
        play_note(NOTE_A5, T16);
        play_note(NOTE_A5, T16);
        play_note(NOTE_A5, T16);
        play_note(NOTE_G5, T8);
        play_note(NOTE_F5, T8);

        play_note(NOTE_E5, T8);
        play_note(NOTE_C5, T8);
        play_note(NOTE_A4, T8);
        play_note(NOTE_G4, T4);
        play_note(NOTE_REST, T8);

        // 10
        play_note(NOTE_E5, T16);
        play_note(NOTE_C5, T16);
        play_note(NOTE_G4, T8);
        play_note(NOTE_REST, T16);

        play_note(NOTE_G4, T8);
        play_note(NOTE_A4, T8);
        play_note(NOTE_F5, T8);
        play_note(NOTE_F5, T16);
        play_note(NOTE_A4, T8);

        play_note(NOTE_B4, T8);
        play_note(NOTE_F5, T16);
        play_note(NOTE_F5, T16);
        play_note(NOTE_F5, T16);
        play_note(NOTE_E5, T8);
        play_note(NOTE_D5, T8);
        play_note(NOTE_C5, T8);

        play_note(NOTE_G4, T8);
        play_note(NOTE_E4, T8);
        play_note(NOTE_C4, T4);
        play_note(NOTE_REST, T8);

        // 11
        play_note(NOTE_C5, T4);
        play_note(NOTE_REST, T8);
        play_note(NOTE_G4, T4);
        play_note(NOTE_REST, T8);
        play_note(NOTE_E4, T4);
        play_note(NOTE_REST, T8);

        play_note(NOTE_A4, T8);
        play_note(NOTE_B4, T8);
        play_note(NOTE_A4, T8);
        play_note(NOTE_REST, T16);

        play_note(NOTE_GS4, T8);
        play_note(NOTE_AS4, T8);
        play_note(NOTE_GS4, T8);
        play_note(NOTE_REST, T16);

        play_note(NOTE_G4, T16);
        play_note(NOTE_FS5, T16);
        play_note(NOTE_G5, T4);

        delay_ms_variable(T2);
    }

    return 0;
}
