#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t time_stop = 0; // volatile: 인터럽트에서 변경될 수 있는 변수임을 명시

int main(void){
    uint8_t led_data = 0x01;
    DDRC = 0x0F; 
    DDRE = 0x00;
    EICRB = 0x03; // INT4, INT5 상승 에지에서 인터럽트 발생
    //EICRB = _BV(ISC41) | _BV(ISC40); // INT4 상승 에지에서 인터럽트 발생
    EIMSK = 0x10; // INT4 인터럽트 허용
    //EIMSK = _BV(INT4); // INT4 인터럽트 허용
    EIFR = 0x10; // INT4 인터럽트 플래그 초기화
    sei(); // 전역 인터럽트 허용

    while(1){
        PORTC = led_data;
        if(time_stop ==0)
        {
            if(led_data == 0x08)
                led_data = 0x01;
            else
                led_data <<=1; 
        }
        _delay_ms(100);
    }
}

SIGNAL(INT4_vect)
{
    cli();
    if(time_stop == 0)
    {
        time_stop =1;
    }
    else{
        time_stop =0;
    }
    sei();
}   