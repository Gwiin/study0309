#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

// ISR(인터럽트 서비스 루틴)와 main이 함께 사용하는 값이므로
// 컴파일러 최적화로 인한 오동작을 막기 위해 volatile로 선언한다.
volatile uint8_t cnt = 0;


int main(void)
{
    // 0~9 숫자를 FND(7-segment)에 표시하기 위한 세그먼트 패턴 테이블
    // 인덱스 0이면 숫자 0, 인덱스 1이면 숫자 1이 표시된다.
    uint8_t FND_DATA_TBL[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x80};

    // PORTA를 출력으로 설정해서 FND 세그먼트 데이터를 내보낸다.
    DDRA = 0xFF;

    // INT4, INT5에 연결된 핀(보드 기준 스위치 입력)을 상승 엣지에서 감지하도록 설정한다.
    // 즉, 스위치를 눌러 Low -> High가 되는 순간 인터럽트가 발생한다.
    EICRB = _BV(ISC41) | _BV(ISC40);  // INT4 상승 엣지
    EICRB |= _BV(ISC51) | _BV(ISC50); // INT5 상승 엣지

    // INT4, INT5 인터럽트를 허용한다.
    EIMSK |= _BV(INT4);
    EIMSK |= _BV(INT5);

    // 전역 인터럽트를 활성화해야 위 설정이 실제로 동작한다.
    sei();

    while (1)
    {
        // 현재 cnt 값에 해당하는 숫자를 계속 FND에 출력한다.
        // 숫자 변경은 ISR에서 하고, 화면 갱신은 main 루프가 담당한다.
        PORTA = FND_DATA_TBL[cnt];
        _delay_ms(100);
    }
}

ISR(INT4_vect)
{
    // INT4 스위치가 눌리면 숫자를 1 증가시킨다.
    // 9 다음에는 다시 0으로 돌아가도록 순환시킨다.
    cnt = (cnt + 1) % 10;
}

ISR(INT5_vect)
{
    // INT5 스위치가 눌리면 숫자를 1 감소시킨다.
    // 0에서 더 내려가면 9로 돌아가도록 순환시킨다.
    if (cnt == 0)
        cnt = 9;
    else
        cnt--;
}
