# git submodule add https://github.com/raspberrypi/pico-sdk.git deps/pico-sdk

cmake_minimum_required(VERSION 3.13)
set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/deps/pico-sdk")
include(pico_sdk_import.cmake)
set(PICO_BOARD "pico2_w" CACHE STRING "Target Raspberry Pi Pico board")
project(my_project C CXX ASM)
pico_sdk_init()

set(WIFI_SSID "bindsoft" CACHE STRING "Wi-Fi SSID for Pico W examples")
set(WIFI_PASSWORD "bindsoft24" CACHE STRING "Wi-Fi password for Pico W examples")
set(MQTT_SERVER "163.152.213.101" CACHE STRING "MQTT broker host")
set(MQTT_PORT 1883 CACHE STRING "MQTT broker port")
set(MQTT_USERNAME "" CACHE STRING "MQTT user name")
set(MQTT_PASSWORD "" CACHE STRING "MQTT password")
set(MQTT_CERT_PATH "${CMAKE_CURRENT_LIST_DIR}/src/mqtt/certs/${MQTT_SERVER}" CACHE PATH "Directory containing MQTT certificates")
set(MQTT_CERT_INC "mqtt_client.inc" CACHE STRING "MQTT certificate include file")

add_executable(blink src/blink.c)
target_link_libraries(blink pico_stdlib)

if (PICO_CYW43_SUPPORTED)
    target_link_libraries(blink pico_cyw43_arch_none)
endif()

pico_enable_stdio_usb(blink 1)
pico_enable_stdio_uart(blink 0)
pico_add_extra_outputs(blink)

add_executable(buzzermario src/buzzermario.c)
target_link_libraries(buzzermario
    pico_stdlib
    hardware_clocks
    hardware_pwm
)
pico_enable_stdio_usb(buzzermario 1)
pico_enable_stdio_uart(buzzermario 0)
pico_add_extra_outputs(buzzermario)

if (PICO_CYW43_SUPPORTED)
    add_executable(mqtt_client src/mqtt/mqtt_client.c)
    target_link_libraries(mqtt_client
        pico_stdlib
        hardware_adc
        pico_cyw43_arch_lwip_threadsafe_background
        pico_lwip_mqtt
        pico_mbedtls
        pico_lwip_mbedtls
    )
    target_include_directories(mqtt_client PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/mqtt
        ${CMAKE_CURRENT_LIST_DIR}/src
    )
    target_compile_definitions(mqtt_client PRIVATE
        WIFI_SSID=\"${WIFI_SSID}\"
        WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
        MQTT_SERVER=\"${MQTT_SERVER}\"
        MQTT_PORT=${MQTT_PORT}
    )
    if (EXISTS "${MQTT_CERT_PATH}/${MQTT_CERT_INC}")
        target_compile_definitions(mqtt_client PRIVATE
            MQTT_CERT_INC=\"${MQTT_CERT_INC}\"
            ALTCP_MBEDTLS_AUTHMODE=MBEDTLS_SSL_VERIFY_REQUIRED
        )
        target_include_directories(mqtt_client PRIVATE
            ${MQTT_CERT_PATH}
        )
    endif()
    if (MQTT_USERNAME AND MQTT_PASSWORD)
        target_compile_definitions(mqtt_client PRIVATE
            MQTT_USERNAME=\"${MQTT_USERNAME}\"
            MQTT_PASSWORD=\"${MQTT_PASSWORD}\"
        )
    endif()
    pico_enable_stdio_usb(mqtt_client 1)
    pico_enable_stdio_uart(mqtt_client 0)
    pico_add_extra_outputs(mqtt_client)

    add_executable(dht22_mqtt src/dht22_mqtt.c)
    target_link_libraries(dht22_mqtt
        pico_stdlib
        hardware_i2c
        pico_cyw43_arch_lwip_threadsafe_background
        pico_lwip_mqtt
        pico_mbedtls
        pico_lwip_mbedtls
    )
    target_include_directories(dht22_mqtt PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/mqtt
        ${CMAKE_CURRENT_LIST_DIR}/src
    )
    target_compile_definitions(dht22_mqtt PRIVATE
        WIFI_SSID=\"${WIFI_SSID}\"
        WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
        MQTT_SERVER=\"${MQTT_SERVER}\"
        MQTT_PORT=${MQTT_PORT}
    )
    if (EXISTS "${MQTT_CERT_PATH}/${MQTT_CERT_INC}")
        target_compile_definitions(dht22_mqtt PRIVATE
            MQTT_CERT_INC=\"${MQTT_CERT_INC}\"
            ALTCP_MBEDTLS_AUTHMODE=MBEDTLS_SSL_VERIFY_REQUIRED
        )
        target_include_directories(dht22_mqtt PRIVATE
            ${MQTT_CERT_PATH}
        )
    endif()
    if (MQTT_USERNAME AND MQTT_PASSWORD)
        target_compile_definitions(dht22_mqtt PRIVATE
            MQTT_USERNAME=\"${MQTT_USERNAME}\"
            MQTT_PASSWORD=\"${MQTT_PASSWORD}\"
        )
    endif()
    pico_enable_stdio_usb(dht22_mqtt 1)
    pico_enable_stdio_uart(dht22_mqtt 0)
    pico_add_extra_outputs(dht22_mqtt)
else()
    message(STATUS "Skipping Wi-Fi examples because PICO_BOARD='${PICO_BOARD}' has no CYW43 support.")
endif()

# Ignore warnings from lwIP's altcp TLS shim.
set_source_files_properties(
    ${PICO_LWIP_PATH}/src/apps/altcp_tls/altcp_tls_mbedtls.c
    PROPERTIES COMPILE_OPTIONS "-Wno-unused-result"
)
