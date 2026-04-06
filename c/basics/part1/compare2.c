#include <stdio.h>

int main()
{
    int num;
    printf("숫자를 넣으세요 1~9 : ");
    scanf("%d" , &num);

    //printf("1 <= %d <= 9 : %d\n",num,(1<=num)&&(num<=9));
    printf("1 <= %d <= 9 : %s\n" ,num, (1<=num)&&(num<=9) ? "true" : "false"); // '?' 삼항 연산자 ( [조건식] ? [참] : [거짓] )
    return 0;
}