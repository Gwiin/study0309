#include "lcd.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

volatile uint16_t ADC_result = 0;

int main(void)
{
    DDRB = 0x10; 
    TCCR0 = 0x62;
    TCNT0 = 0x00;
    ADMUX = 0x41; //ADC1 선택, single mode, 1번 채널, 3.3V 외부 기준 전압(AREF)
    ADCSRA = 0xAF; 
    ADCSRA |= 0x40; 
    sei();

    lcdInit();
    lcdGotoXY(0, 0);
    lcdPrintData("Variable register",strlen("Variable register"));

    while(1)
    {
        OCR0 = ADC_result;
        
        {
            char buf[16];
            sprintf(buf, "R:%u  ", ADC_result);
            lcdGotoXY(0, 1);
            lcdPrintData(buf, strlen(buf));
        }
        _delay_ms(200);
        
    }
    return 0;
}


ISR(ADC_vect)
{
    cli();
    ADC_result = ADC;
    sei();
}