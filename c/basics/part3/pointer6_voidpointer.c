#include<stdio.h>

int main(void){

    int i=100;
    double d = 3.14;

    void *p;
    p = &i;
    *(int *)p=200;
    printf("i : %d, *p : %d\n",i,*(int *)p);
    return 0;
}