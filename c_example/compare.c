#include <stdio.h>
#include <stdbool.h> //c에서 true false 를 명시적으로 쓸때 stdbool헤더를 쓴다

int main()
{
    int a,b;
    bool greater = false;
    printf("두 점수를 입력하세요 : ");
    scanf("%d %d",&a, &b);

    greater = a > b;
    printf("greater의 값은 %d 이다.\n",greater);
    if(greater == true)
        printf("a가 더 크다.\n");
    else
        printf("a가 더 작다.\n");


    return 0;
}