#include <avr/io.h>

int main(void){

    DDRC = 0x0F;
    DDRE = 0x00;
    while(1){
        PORTC = PINE >> 4;
    }
}