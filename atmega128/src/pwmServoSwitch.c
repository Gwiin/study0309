#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <lcd.h>

static uint16_t servo_pulse_from_angle(uint8_t angle)
{
    if (angle > 180)
    {
        angle = 180;
    }

    return 2000 + (uint32_t)angle * 2000 / 180;
}

int main(void)
{
    uint8_t switch_flag = 0;
    uint8_t selected_angle = 0;
    uint8_t current_angle = 255;
    uint16_t pulse = 2000;

    char buffer[16];

    DDRC = 0x0F;
    PORTC = 0x00;

    // PE3(OC3A)는 서보 PWM 출력, PE4~PE7은 스위치 입력으로 사용한다.
    DDRE = _BV(PE3);

    TCCR3A = _BV(COM3A1) | _BV(WGM31);
    TCCR3B = _BV(WGM33) | _BV(WGM32) | _BV(CS31);
    // 분주비 8, Fast PWM, TOP=ICR3, OC3A 비반전 출력

    ICR3 = 40000; // 20ms 주기(50Hz)
    OCR3A = servo_pulse_from_angle(0);

    lcdInit();
    lcdClear();

    while (1)
    {
        switch_flag = (PINE >> 4) & 0x0F;
        PORTC = switch_flag;

        // 한 번에 하나의 스위치만 눌렸을 때만 각도를 바꾼다.
        if (switch_flag == 0x01)
        {
            selected_angle = 0;
        }
        else if (switch_flag == 0x02)
        {
            selected_angle = 45;
        }
        else if (switch_flag == 0x04)
        {
            selected_angle = 90;
        }
        else if (switch_flag == 0x08)
        {
            selected_angle = 135;
        }

        if (selected_angle != current_angle)
        {
            pulse = servo_pulse_from_angle(selected_angle);
            OCR3A = pulse;
            current_angle = selected_angle;

            lcdGotoXY(0, 0);
            lcdPrint("Angle: ");
            itoa(current_angle, buffer, 10);
            lcdPrint(buffer);
            lcdPrint("    ");

            _delay_ms(20);
        }
    }

    return 0;
}
