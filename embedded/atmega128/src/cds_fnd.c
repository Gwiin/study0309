#include "lcd.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

// ADC 변환이 끝날 때마다 인터럽트에서 최신 CDS 값을 저장한다.
// main 함수와 ISR이 함께 사용하는 값이므로 volatile로 선언한다.
volatile uint16_t ADC_result = 0;

// 실습에서 관찰한 CDS 최대 측정값을 보정 기준으로 사용한다.
// 765 이상이 들어오면 가장 높은 단계인 10으로 처리한다.
static const uint16_t ADC_MAX_CALIBRATED = 765;

static uint8_t adc_to_level(uint16_t adc_value)
{
    uint8_t level;

    // 보정 기준 이상이면 최댓값 단계 10을 바로 반환한다.
    if (adc_value >= ADC_MAX_CALIBRATED)
    {
        return 10;
    }

    // ADC 실제 측정 범위 0~765를 11단계(0~10)로 나눈다.
    // 예를 들어 0에 가까우면 0, 765에 가까우면 10에 가까운 값이 된다.
    level = (uint8_t)((adc_value * 11UL) / (ADC_MAX_CALIBRATED + 1UL));

    return level;
}

int main(void)
{
    // 7세그먼트 FND에 출력할 패턴 테이블이다.
    // 인덱스 0~9는 숫자 0~9를 뜻하고,
    // 인덱스 10은 한 자리 FND에서 최댓값 단계를 나타내기 위해 'A'로 표시한다.
    uint8_t fnd_data_tbl[] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66,
        0x6D, 0x7C, 0x07, 0x7F, 0x67,
        0x77
    };

    // PORTA를 FND 출력 포트로 사용한다.
    // 각 비트가 a,b,c,d,e,f,g,dp 세그먼트 on/off에 대응한다.
    DDRA = 0xFF;

    // 시작할 때는 0단계를 먼저 표시한다.
    PORTA = fnd_data_tbl[0];

    // ADC0 핀에 연결된 CDS 값을 읽는다.
    ADMUX = 0x40;

    // ADC 사용 허가, 자동 트리거, 인터럽트 허가, 분주비 128 설정이다.
    // 분주비를 크게 잡아 ADC가 안정적으로 변환되도록 한다.
    ADCSRA = 0xAF;

    // ADC 변환을 시작한다.
    // 이후에는 자동 트리거 설정에 따라 계속 변환이 이어진다.
    ADCSRA |= 0x40;

    // LCD 초기화 후 첫 줄에 현재 프로그램 성격과 보정 기준을 표시한다.
    lcdInit();
    lcdGotoXY(0, 0);
    lcdPrintData("CDS CAL:765", strlen("CDS CAL:765"));

    // ADC 인터럽트가 동작하도록 전역 인터럽트를 켠다.
    sei();

    while (1)
    {
        // 최신 ADC 원시값을 0~10 단계로 변환한다.
        uint8_t level = adc_to_level(ADC_result);

        // LCD 둘째 줄에 보여줄 문자열 버퍼다.
        char buf[16];

        // 계산된 단계값에 해당하는 FND 패턴을 출력한다.
        PORTA = fnd_data_tbl[level];

        // LCD 둘째 줄에 현재 ADC 값과 단계값을 함께 보여준다.
        // L은 ADC 원시값(실제 측정값), F는 Level(구간화된 단계값)이다.
        sprintf(buf, "L:%4u F:%2u", ADC_result, level);
        lcdGotoXY(0, 1);
        lcdPrintData(buf, strlen(buf));

        // 화면과 FND가 너무 빠르게 바뀌지 않도록 잠시 대기한다.
        _delay_ms(50);
    }

    return 0;
}

ISR(ADC_vect)
{
    // ADC 변환이 끝날 때마다 결과 레지스터 값을 전역 변수에 저장한다.
    ADC_result = ADC;
}
