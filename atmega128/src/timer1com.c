#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t FND_DATA_TBL[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x08};
volatile uint8_t time_s = 0x01;
volatile uint8_t timer1_cnt;

int main(void)
{
    DDRA = 0xFF;
    DDRE = 0x00;

    TCCR1A = 0x00; 
    TCCR1B = 0x05; 

    OCR1A = 14400; // 65535 = 2^16 -> 14400에서 trigger 발생 -> 0.1초마다 인터럽트 발생
    OCR1B = 28800; // 28800에서 trigger 발생 -> 0.2초마다 인터럽트 발생
    TIMSK = _BV(OCIE1A) | _BV(OCIE1B) | _BV(TOIE1); // OCR1A, OCR1B, overflow 인터럽트 허용
    sei();

    PORTA = FND_DATA_TBL[0]; 
    while(1)
    {
        PORTA = FND_DATA_TBL[time_s]; 
        if(time_s>10)
            time_s =0;
    }
    return 0;
}

ISR(TIMER1_COMPA_vect){
    cli();
    time_s++;
    sei();
}

ISR(TIMER1_COMPB_vect){
    cli();
    time_s--;
    sei();
}

ISR(TIMER1_OVF_vect){
    cli();
    time_s++;
    sei();
}

