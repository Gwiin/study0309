#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
    // 기본 실험: PB4(OC0)
    DDRC = 0x00;
    DDRB |= _BV(PB4);

    TCCR0 = _BV(WGM00) | _BV(WGM01) | _BV(COM01) | _BV(CS01);

    // PB5(OC1A) 실험용
    DDRB |= _BV(PB5);
    TCCR1A = _BV(WGM10) | _BV(COM1A1);
    TCCR1B = _BV(WGM12) | _BV(CS11);
    
    // PB6(OC1B) 실험용
    DDRB |= _BV(PB6);
    TCCR1A = _BV(WGM10) | _BV(COM1B1);
    TCCR1B = _BV(WGM12) | _BV(CS11);
    
    // PB7(OC2) 실험용
    DDRB |= _BV(PB7);
    TCCR2 = _BV(WGM20) | _BV(WGM21) | _BV(COM21) | _BV(CS21);
    

    uint8_t brightness = 0;
    int8_t delta = 1;

    while (1)
    {
        OCR0 = brightness;

        OCR1A = brightness; // PB5 실험 시 사용
        OCR1B = brightness; // PB6 실험 시 사용
        OCR2 = brightness;  // PB7 실험 시 사용

        _delay_ms(10);
        brightness += delta;

        if (brightness == 0 || brightness == 255)
        {
            delta = -delta;
        }
    }

    return 0;
}
