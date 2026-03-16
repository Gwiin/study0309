#include <stdio.h>

enum season {SPRING, SUMMER, FALL, WINTER};

int main(void){

    enum season ss;
    char *pString = NULL;

    ss = SPRING;
    switch(ss)
    {
        case SPRING:
            pString = "inline";
            break;
        case SUMMER:
            pString = "swimming";
            break;
        case FALL:
            pString = "trip";
            break;
        case WINTER:
            pString = "skiing";
            break;
    }
    printf("나의 레저 활동 => %s\n",pString);
    return 0;
}