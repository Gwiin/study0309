#include <avr/io.h>
#include <util/delay.h>


// https://noobnotes.net/super-mario-bros-theme-nintendo/?solfege=false

#define NOTE_REST 0
#define NOTE_E5 659
#define NOTE_C5 523
#define NOTE_G5 784
#define NOTE_G4 392
#define NOTE_E4 330
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_AS4 466
#define NOTE_FS5 740
#define NOTE_A5 880
#define NOTE_F5 698
#define NOTE_D5 587
#define NOTE_C6 1046
#define NOTE_C4 262
#define NOTE_GS4 415
#define NOTE_DS5 622

#define T16 75
#define T8  150
#define T4  300
#define T2  600

static void delay_ms_variable(uint16_t duration_ms)
{
    while (duration_ms--)
    {
        _delay_ms(1);
    }
}

static void play_note(uint16_t freq, uint16_t duration_ms)
{
    if (freq == NOTE_REST)
    {
        OCR1C = 0;
        delay_ms_variable(duration_ms);
        return;
    }

    ICR1 = (uint16_t)(14745600UL / freq);
    OCR1C = ICR1 / 2;
    delay_ms_variable(duration_ms);
    OCR1C = 0;
    delay_ms_variable(30);
}

int main(void)
{
    // PB7 = OC1C, 버저 출력 핀
    DDRB |= _BV(PB7);

    // Timer1 Fast PWM, OC1C 사용, 분주비 1
    TCCR1A = _BV(COM1C1) | _BV(WGM11);
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);

    while (1)
    {
        // Super Mario Bros. Overworld Theme ver.gpt
        
        // 1
        play_note(NOTE_E5, T8);   
        play_note(NOTE_REST, T16);
        play_note(NOTE_E5, T8);  
        play_note(NOTE_REST, T8);
        play_note(NOTE_E5, T8);   
        play_note(NOTE_REST, T8);

        play_note(NOTE_C5, T8);   
        play_note(NOTE_REST, T16);
        play_note(NOTE_E5, T8);   
        play_note(NOTE_REST, T8);
        play_note(NOTE_G5, T4);   
        play_note(NOTE_REST, T4);
        play_note(NOTE_G4, T4);   
        play_note(NOTE_REST, T4);

        // 2
        play_note(NOTE_C5, T4);   
        play_note(NOTE_REST, T8);
        play_note(NOTE_G4, T4);   
        play_note(NOTE_REST, T8);
        play_note(NOTE_E4, T4);   
        play_note(NOTE_REST, T8);

        play_note(NOTE_A4, T8);
        play_note(NOTE_B4, T8);
        play_note(NOTE_AS4, T16);
        play_note(NOTE_A4, T8);  
        play_note(NOTE_REST, T16);

        play_note(NOTE_G4, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_G5, T8);
        play_note(NOTE_A5, T4);   
        play_note(NOTE_REST, T16);

        play_note(NOTE_F5, T8);
        play_note(NOTE_G5, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_C5, T8);
        play_note(NOTE_D5, T8);
        play_note(NOTE_B4, T4);  
        play_note(NOTE_REST, T8);

        // 3
        play_note(NOTE_C5, T4);   
        play_note(NOTE_REST, T8);
        play_note(NOTE_G4, T4);   
        play_note(NOTE_REST, T8);
        play_note(NOTE_E4, T4);   
        play_note(NOTE_REST, T8);

        play_note(NOTE_A4, T8);
        play_note(NOTE_B4, T8);
        play_note(NOTE_AS4, T16);
        play_note(NOTE_A4, T8);   
        play_note(NOTE_REST, T16);

        play_note(NOTE_G4, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_G5, T8);
        play_note(NOTE_A5, T4);   
        play_note(NOTE_REST, T16);

        play_note(NOTE_F5, T8);
        play_note(NOTE_G5, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_C5, T8);
        play_note(NOTE_D5, T8);
        play_note(NOTE_B4, T4);   
        play_note(NOTE_REST, T8);

        // 4
        play_note(NOTE_G5, T16);
        play_note(NOTE_FS5, T16);
        play_note(NOTE_F5, T16);
        play_note(NOTE_D5, T8);
        play_note(NOTE_E5, T8);   
        play_note(NOTE_REST, T16);

        play_note(NOTE_G4, T8);
        play_note(NOTE_A4, T8);
        play_note(NOTE_C5, T4);

        play_note(NOTE_A4, T8);
        play_note(NOTE_C5, T8);
        play_note(NOTE_D5, T4);   
        play_note(NOTE_REST, T8);

        play_note(NOTE_G5, T16);
        play_note(NOTE_FS5, T16);
        play_note(NOTE_F5, T16);
        play_note(NOTE_D5, T8);
        play_note(NOTE_E5, T8);   
        play_note(NOTE_REST, T16);

        play_note(NOTE_C6, T8);
        play_note(NOTE_C6, T16);
        play_note(NOTE_C6, T4);   
        play_note(NOTE_REST, T8);

        // 5
        play_note(NOTE_G5, T16);
        play_note(NOTE_FS5, T16);
        play_note(NOTE_F5, T16);
        play_note(NOTE_D5, T8);
        play_note(NOTE_E5, T8);   
        play_note(NOTE_REST, T16);

        play_note(NOTE_G4, T8);
        play_note(NOTE_A4, T8);
        play_note(NOTE_C5, T4);

        play_note(NOTE_A4, T8);
        play_note(NOTE_C5, T8);
        play_note(NOTE_D5, T4);   
        play_note(NOTE_REST, T8);

        play_note(NOTE_DS5, T8);
        play_note(NOTE_D5, T8);
        play_note(NOTE_C5, T4);   
        play_note(NOTE_REST, T4);

        // 6
        play_note(NOTE_C5, T8);
        play_note(NOTE_C5, T16);
        play_note(NOTE_C5, T8);   
        play_note(NOTE_REST, T16);

        play_note(NOTE_C5, T8);
        play_note(NOTE_D5, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_C5, T8);
        play_note(NOTE_A4, T8);
        play_note(NOTE_G4, T4);   
        play_note(NOTE_REST, T8);

        play_note(NOTE_C5, T8);
        play_note(NOTE_C5, T16);
        play_note(NOTE_C5, T8);   
        play_note(NOTE_REST, T16);

        play_note(NOTE_C5, T8);
        play_note(NOTE_D5, T8);
        play_note(NOTE_E5, T4);   
        play_note(NOTE_REST, T4);

        // 7
        play_note(NOTE_C5, T8);
        play_note(NOTE_C5, T16);
        play_note(NOTE_C5, T8);   
        play_note(NOTE_REST, T16);

        play_note(NOTE_C5, T8);
        play_note(NOTE_D5, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_C5, T8);
        play_note(NOTE_A4, T8);
        play_note(NOTE_G4, T4);   
        play_note(NOTE_REST, T8);

        play_note(NOTE_E5, T8);   
        play_note(NOTE_REST, T16);
        play_note(NOTE_E5, T8);   
        play_note(NOTE_REST, T8);
        play_note(NOTE_E5, T8);   
        play_note(NOTE_REST, T8);

        play_note(NOTE_C5, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_G5, T4);
        play_note(NOTE_G4, T4);   
        play_note(NOTE_REST, T4);

        // 8
        play_note(NOTE_C5, T4);   
        play_note(NOTE_REST, T8);
        play_note(NOTE_G4, T4);   
        play_note(NOTE_REST, T8);
        play_note(NOTE_E4, T4);   
        play_note(NOTE_REST, T8);

        play_note(NOTE_A4, T8);
        play_note(NOTE_B4, T8);
        play_note(NOTE_AS4, T16);
        play_note(NOTE_A4, T8);   
        play_note(NOTE_REST, T16);

        play_note(NOTE_G4, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_G5, T8);
        play_note(NOTE_A5, T4);   
        play_note(NOTE_REST, T16);

        play_note(NOTE_F5, T8);
        play_note(NOTE_G5, T8);
        play_note(NOTE_E5, T8);
        play_note(NOTE_C5, T8);
        play_note(NOTE_D5, T8);
        play_note(NOTE_B4, T4);   
        play_note(NOTE_REST, T8);

        // 9
        play_note(NOTE_E5, T16);
        play_note(NOTE_C5, T16);
        play_note(NOTE_G4, T8);   
        play_note(NOTE_REST, T16);

        play_note(NOTE_G4, T8);
        play_note(NOTE_A4, T8);
        play_note(NOTE_F5, T8);
        play_note(NOTE_F5, T16);
        play_note(NOTE_A4, T8);

        play_note(NOTE_B4, T8);
        play_note(NOTE_A5, T16);
        play_note(NOTE_A5, T16);
        play_note(NOTE_A5, T16);
        play_note(NOTE_G5, T8);
        play_note(NOTE_F5, T8);

        play_note(NOTE_E5, T8);
        play_note(NOTE_C5, T8);
        play_note(NOTE_A4, T8);
        play_note(NOTE_G4, T4);   
        play_note(NOTE_REST, T8);

        // 10
        play_note(NOTE_E5, T16);
        play_note(NOTE_C5, T16);
        play_note(NOTE_G4, T8);   
        play_note(NOTE_REST, T16);

        play_note(NOTE_G4, T8);
        play_note(NOTE_A4, T8);
        play_note(NOTE_F5, T8);
        play_note(NOTE_F5, T16);
        play_note(NOTE_A4, T8);

        play_note(NOTE_B4, T8);
        play_note(NOTE_F5, T16);
        play_note(NOTE_F5, T16);
        play_note(NOTE_F5, T16);
        play_note(NOTE_E5, T8);
        play_note(NOTE_D5, T8);
        play_note(NOTE_C5, T8);

        play_note(NOTE_G4, T8);
        play_note(NOTE_E4, T8);
        play_note(NOTE_C4, T4);   
        play_note(NOTE_REST, T8);

        // 11
        play_note(NOTE_C5, T4);   
        play_note(NOTE_REST, T8);
        play_note(NOTE_G4, T4);   
        play_note(NOTE_REST, T8);
        play_note(NOTE_E4, T4);   
        play_note(NOTE_REST, T8);

        play_note(NOTE_A4, T8);
        play_note(NOTE_B4, T8);
        play_note(NOTE_A4, T8);   
        play_note(NOTE_REST, T16);

        play_note(NOTE_GS4, T8);
        play_note(NOTE_AS4, T8);
        play_note(NOTE_GS4, T8);  
        play_note(NOTE_REST, T16);

        play_note(NOTE_G4, T16);
        play_note(NOTE_FS5, T16);
        play_note(NOTE_G5, T4);
        


        delay_ms_variable(600);
    }

    return 0;
}





/*
        play_note(NOTE_E5, 150);
        play_note(NOTE_E5, 150);
        play_note(NOTE_REST, 150);
        play_note(NOTE_E5, 150);
        play_note(NOTE_REST, 150);
        play_note(NOTE_C5, 150);
        play_note(NOTE_E5, 300);
        play_note(NOTE_G5, 300);
        play_note(NOTE_REST, 300);
        play_note(NOTE_G4, 300);
        play_note(NOTE_REST, 300);

        play_note(NOTE_C5, 300);
        play_note(NOTE_REST,150);
        play_note(NOTE_G4, 300);
        play_note(NOTE_REST,150);
        play_note(NOTE_E4, 300);
        play_note(NOTE_REST, 150);
        play_note(NOTE_A4, 300);
        play_note(NOTE_B4, 300);
        play_note(NOTE_AS4, 150);
        play_note(NOTE_A4, 300);
        play_note(NOTE_G4, 200);
        play_note(NOTE_E5, 200);
        play_note(NOTE_G5, 200);
        play_note(NOTE_A5, 300);
        play_note(NOTE_F5, 150);
        play_note(NOTE_G5, 150);
        play_note(NOTE_REST, 150);
        play_note(NOTE_E5, 300);
        play_note(NOTE_C5, 150);
        play_note(NOTE_D5, 150);
        play_note(NOTE_B4, 300);
        play_note(NOTE_REST, 150);


        //-----

        play_note(NOTE_REST, 300);
        play_note(NOTE_C5, 150);
        play_note(NOTE_G4, 150);
        play_note(NOTE_E4, 150);
        play_note(NOTE_A4, 300);
        play_note(NOTE_B4, 150);
        play_note(NOTE_REST, 150);
        play_note(NOTE_AS4, 150);
        play_note(NOTE_A4, 150);
        play_note(NOTE_G4, 150);
        play_note(NOTE_REST, 150);
        play_note(NOTE_E5, 150);
        play_note(NOTE_G5, 150);
        play_note(NOTE_A4, 150);
        play_note(NOTE_REST, 300);
        play_note(NOTE_F5, 150);
        play_note(NOTE_G5, 150);
        play_note(NOTE_E5, 150);
        play_note(NOTE_C5, 300);
        play_note(NOTE_D5, 150);
        play_note(NOTE_B4, 250);

        play_note(NOTE_G5, 250);
        play_note(NOTE_FS5, 250);
        play_note(NOTE_F5, 250);
        play_note(NOTE_D5, 250);
        play_note(NOTE_E5, 250);
        play_note(NOTE_G4, 250);
        play_note(NOTE_A4, 250);
        play_note(NOTE_C5, 250);
        play_note(NOTE_A4, 250);
        play_note(NOTE_C5, 250);
        play_note(NOTE_D5, 250);
        play_note(NOTE_G5, 250);
        play_note(NOTE_FS5, 250);
        play_note(NOTE_F5, 250);
        play_note(NOTE_D5, 250);
        play_note(NOTE_E5, 250);
        play_note(NOTE_C6, 250);
        play_note(NOTE_C6, 250);
        play_note(NOTE_C6, 250);
        */