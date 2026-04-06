#include <stdio.h>

int main()
{
    int celsius;
    printf("C 온도를 넣으세요: ");
    scanf("%d",&celsius);
    double fahr;
    fahr = 9.0 / 5.0 * (double)celsius + 32; //celsius 가 double형이 되었다가 다시 int형으로 돌아옴
    printf("C(celsius)온도 : %d\n", celsius);
    printf("F(fahr)온도 : %.2f\n", fahr);
    return 0;
}
