#include <stdio.h>

int main(void)
{
    double length;
    double height;
    double area;

    printf("삼각형의 길이를 넣으세요 : ");
    scanf("%lf %lf",&length, &height);
    area = length * height / 2;
    printf("삼각형의 넓이는 : %.2f\n", area); // %.2f -> 소수점 두자리까지
    return 0;
}