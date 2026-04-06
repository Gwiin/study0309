#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint16_t ADC_result = 0;
static const uint16_t PWM_TOP = 800;
static const uint16_t MOTOR_MIN_DUTY = 160;


int main(void)
{
    // PD4, PD5는 모터 방향 제어, PB5(OC1A)는 PWM 출력으로 사용한다.
    DDRD = _BV(PD4) | _BV(PD5);
    DDRB = _BV(PB5);

    // Timer1 Fast PWM, TOP=ICR1, 비반전 출력, 분주비 8 설정
    TCCR1A = _BV(COM1A1) | _BV(WGM11);
    TCCR1B = _BV(CS11) | _BV(WGM12) | _BV(WGM13);
    // 16MHz / 8 = 2MHz 이므로 카운트 1개는 0.5us
    // TOP=800이면 PWM 주기는 약 400us, 주파수는 약 2.5kHz
    ICR1 = PWM_TOP;
    OCR1A = 0;


    // 가변저항 입력을 ADC1에서 읽는다.
    // 회로가 ADC0에 연결돼 있다면 0x40으로 바꿔야 한다.
    ADMUX = 0x41;

    // ADC enable, auto trigger, interrupt enable, prescaler 128
    ADCSRA = 0xAF;
    ADCSRA |= 0x40;

    // 모터 회전 방향을 한쪽으로 고정한다.
    sei();

    PORTD &= ~_BV(PD5);
    PORTD |= _BV(PD4);


    while(1)
    {
        // ADC 0~1023 값을 PWM 0~800으로 변환한다.
        uint16_t pwm = (uint32_t)ADC_result * PWM_TOP / 1023;

        // 모터는 너무 낮은 듀티에서 아예 안 돌 수 있어서
        // 값이 조금이라도 들어오면 최소 듀티 이상으로 올린다.
        if (ADC_result > 0 && pwm < MOTOR_MIN_DUTY)
        {
            pwm = MOTOR_MIN_DUTY;
        }

        if (pwm > PWM_TOP)
        {
            pwm = PWM_TOP;
        }

        OCR1A = pwm;
        _delay_ms(50);
        
    }
    return 0;
}


ISR(ADC_vect)
{
    ADC_result = ADC;
}
