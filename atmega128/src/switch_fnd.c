// 스위치를 눌렀을 때 fnd 숫자가 증가하는 코드를 작성하세요.
// PINE0 -> +1 , PINE1 -> -1
// 스위치를 오래 눌러도 한번만 변환하게 할것!
// 숫자 범위는 0 ~ 9 까지
// 9가 넘어가면 0을 표시하세요.
// 0 아래로 가면 9를 표시하세요.
#include <avr/io.h>

int main(void)
{
    uint8_t FND_DATA_TBL[] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66,
        0x6D, 0x7C, 0x07, 0x7F, 0x67
    };

    uint8_t cnt = 0;
    uint8_t switch_flag = 0, switch_flag_pre = 0;

    DDRA = 0xFF;
    DDRE = 0x00;

    PORTA = FND_DATA_TBL[cnt];

    while (1)
    {
        if (switch_flag != (PINE >> 4)) {
            switch_flag = PINE >> 4;

            if (switch_flag == 0x01 || switch_flag == 0x02) {
                switch_flag_pre = switch_flag;

                if (switch_flag_pre == 0x01) {
                    cnt++;
                    if (cnt > 9)
                        cnt = 0;
                }
                else if (switch_flag_pre == 0x02) {
                    if (cnt == 0)
                        cnt = 9;
                    else
                        cnt--;
                }

                PORTA = FND_DATA_TBL[cnt];
            }
        }
    }

    return 0;
}