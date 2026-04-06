cmake_minimum_required(VERSION 3.10)

# standalone configure일 때만 기본 AVR 툴체인 파일을 지정한다.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/avr-toolchain.cmake")
endif()

project(Atmega128_Project C)

# --- 하드웨어 설정 ---
set(MCU atmega128)
set(F_CPU 16000000UL)
set(PROG_TYPE stk500v2)
set(PROG_PORT usb)

# --- 공용 UART0 라이브러리 ---
add_library(uart0 STATIC lib/uart0/uart0.c)
target_include_directories(uart0 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/uart0
)
target_compile_options(uart0 PUBLIC
    -mmcu=${MCU}
    -DF_CPU=${F_CPU}
    -Os -Wall
)

# --- 공용 LCD 라이브러리 ---
add_library(lcd STATIC lib/lcd/lcd.c)
target_include_directories(lcd PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/lcd
)
target_compile_options(lcd PUBLIC
    -mmcu=${MCU}
    -DF_CPU=${F_CPU}
    -Os -Wall
)

# --- 공용 SHT20(TWI) 라이브러리 ---
add_library(sht20 STATIC
    lib/sht20/SHT2x.c
    lib/sht20/TWI_driver.c
)
target_include_directories(sht20 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/sht20
)
target_compile_options(sht20 PUBLIC
    -mmcu=${MCU}
    -DF_CPU=${F_CPU}
    -Os -Wall
)

# --- 공용 AT25 SPI EEPROM 라이브러리 ---
add_library(at25 STATIC
    lib/at25/at25160.c
)
target_include_directories(at25 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/at25
)
target_compile_options(at25 PUBLIC
    -mmcu=${MCU}
    -DF_CPU=${F_CPU}
    -Os -Wall
)

# --- 1. src 폴더의 모든 .c 파일 목록 가져오기 ---
# CONFIGURE_DEPENDS를 사용하면 새 소스 파일이 추가되어도 빌드 시 자동으로 재설정된다.
file(GLOB SRC_FILES CONFIGURE_DEPENDS "src/*.c")

# --- 2. 각 파일별로 빌드 및 업로드 타겟 자동 생성 ---
foreach(SOURCE_FILE ${SRC_FILES})
    # 파일 경로에서 확장자를 제외한 이름만 추출 (예: src/fnd1.c -> fnd1)
    get_filename_component(EXE_NAME ${SOURCE_FILE} NAME_WE)

    # --- 실행 파일 및 옵션 ---
    add_executable(${EXE_NAME}.elf ${SOURCE_FILE})

    target_compile_options(${EXE_NAME}.elf PUBLIC
        -mmcu=${MCU}
        -DF_CPU=${F_CPU}
        -Os -Wall
    )
    target_include_directories(${EXE_NAME}.elf PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/uart0
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/lcd
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/sht20
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/at25
    )
    target_link_libraries(${EXE_NAME}.elf PUBLIC uart0 lcd sht20 at25)

    target_link_options(${EXE_NAME}.elf PUBLIC -mmcu=${MCU})

    # --- 빌드 후처리 (HEX 생성) ---
    add_custom_command(TARGET ${EXE_NAME}.elf POST_BUILD
        COMMAND avr-objcopy -j .text -j .data -O ihex ${EXE_NAME}.elf ${EXE_NAME}.hex
        COMMAND avr-size --format=avr --mcu=${MCU} ${EXE_NAME}.elf
        COMMENT "Generating Intel HEX file and analysis"
    )

    # --- 업로드 타겟 추가 ---
    add_custom_target(upload_${EXE_NAME}
        COMMAND avrdude -p m128 -c ${PROG_TYPE} -P ${PROG_PORT} -U flash:w:${EXE_NAME}.hex:i
        DEPENDS ${EXE_NAME}.elf
        COMMENT "Flashing ${EXE_NAME}.hex to hardware..."
    )
endforeach()
