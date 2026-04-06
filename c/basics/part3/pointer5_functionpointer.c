#include<stdio.h>

int add(int a,int b);
int substract(int a,int b);

int main(void){

    int (*fp)(int,int); //함수 포인터 선언
    fp = add; //함수 포인터에 add 함수의 주소를 할당
    int re = (*fp)(4,3); 
    printf("result: %d\n",re); 

    fp = &substract;
    re = (*fp)(4,3);
    printf("re : %d\n",re);
    return 0;
}


int add(int a,int b){
    return a+b;
}

int substract(int a,int b){
    return a-b; 
}