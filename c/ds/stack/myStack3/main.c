#include "stack3.h"


int main(void)
{
    Stack s1, s2;
    initStack(&s1,10);
    initStack(&s2,100);

    push(&s1, 100);
    push(&s1, 200);
    push(&s1, 300);

    printf("s1 First pop() : %d\n", pop(&s1));
    printf("s1 Second pop() : %d\n", pop(&s1));
    printf("s1 Third pop() : %d\n", pop(&s1));

    push(&s2, 700);
    push(&s2, 800);
    push(&s2, 900);

    printf("s2 First pop() : %d\n", pop(&s2));
    printf("s2 Second pop() : %d\n", pop(&s2));
    printf("s2 Third pop() : %d\n", pop(&s2));


    printf("s1 stack memory size : %d\n", s1.size);
    printf("s2 stack memory size : %d\n", s2.size);


    cleanupStack(&s1);
    cleanupStack(&s2);
    return 0;

}