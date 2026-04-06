#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t txFlag = 0;
volatile int8_t txData = 0;

uint8_t getch(void)
{
    uint8_t data;
    while((UCSR0A & 0x80) == 0)
        ;
    data = UDR0;
    UCSR0A |= 0x80;
    return data;
}

int main(void){
    uint8_t numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x08};
    uint8_t rx_data;
    DDRA = 0xFF;

    UCSR0A = 0x00;
    UCSR0B = 0x18; //0x00011000 rx tx 인터럽트 허용, 송수신 허용
    UCSR0C = 0x16; //0b00010110 8비트 데이터, 패리티 없음, 1비트 스톱비트

    UBRR0H = 0x00;
    UBRR0L = 0x07; // 115200 bps

    while(1){
        rx_data = getch();
        if((rx_data >= 0x30) && (rx_data <= 0x39)){
            PORTA = numbers[rx_data - 0x30];
        }
    }
    return 0;

}

