#include <stdio.h>

int main(){
    int *p;
    int Value;
    p = &Value;
    *p = 200;
    printf("포인터 주소 : %p, 가리키는 값 : %d\n",p,*p);
    return 0;
}