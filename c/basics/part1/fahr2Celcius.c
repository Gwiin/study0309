#include <stdio.h>

int main()
{
    int fahr;
    double celcius;
    printf("F(fahr)온도 값을 입력 : ");
    scanf("%d", &fahr);
    celcius = ((double)fahr-32) * 5.0 / 9.0;
    printf("F(fahr)온도 : %d\n",fahr);
    printf("C(celcius)온도 : %.1f\n", celcius);
    return 0;
}