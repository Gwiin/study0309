#include <stdio.h>

typedef struct
{
    int year;
    int month;
    int day;
}Date; //typedef struct data Date; //data라는 이름 대신 Date라는 이름으로 구조체를 사용할 수 있도록 하는 typedef 선언입니다.

//typedef를 사용했을때의 장점 : typedef를 사용하면 구조체를 선언할 때마다 struct 키워드를 반복해서 작성할 필요가 없습니다. 예를 들어, typedef를 사용하지 않으면 구조체 변수를 선언할 때마다 struct data d;와 같이 작성해야 하지만, typedef를 사용하면 Date d;와 같이 간단하게 작성할 수 있습니다. 이는 코드의 가독성을 향상시키고, 구조체를 더 쉽게 사용할 수 있도록 도와줍니다.


int main(void)
{
    Date d;
    Date *pD;
    d.year = 2026;
    d.month = 7;
    d.day = 15;

    Date d2 = {.year = 2026, .month = 7, .day = 15}; //구조체 초기화 방법 중 하나인 지정 초기화입니다. 이 방법을 사용하면 구조체 멤버의 이름을 명시적으로 지정하여 초기화할 수 있습니다. 예를 들어, Date d2 = {.year = 2026, .month = 7, .day = 15};와 같이 작성하면 d2 구조체의 year 멤버는 2026으로, month 멤버는 7로, day 멤버는 15로 초기화됩니다. 이 방법은 구조체 멤버의 순서에 상관없이 초기화할 수 있기 때문에 가독성이 좋고, 실수를 줄이는 데 도움이 됩니다.

    pD = &d;


    printf("%d-%d-%d\n", d.year, d.month, d.day);
    printf("%d-%d-%d\n", (*pD).year, (*pD).month, (*pD).day); 
    printf("%d-%d-%d\n", pD->year, pD->month, pD->day);

    return 0;
}