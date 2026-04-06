#include <stdio.h>
#include <stdlib.h>

int main(void){

    char *pLiteral = "리터럴 상수이다.";
    int *pInt;
    double *pDouble;
    char pLocalVariable = 'C';
    char pArray[30] = "지역 변수 (배열)";

    pInt = (int *)malloc(sizeof(int)); //malloc() 함수를 사용하여 int형 크기만큼 메모리를 동적으로 할당합니다. 반환된 포인터는 void* 타입이므로, int* 타입으로 캐스팅하여 pInt에 저장합니다.
    if(pInt == NULL)
    {
        printf("메모리가 부족합니다\n");
        exit(1);
    }
    pDouble = (double *)malloc(sizeof(double)); //malloc() 함수를 사용하여 double형 크기만큼 메모리를 동적으로 할당합니다. 반환된 포인터는 void* 타입이므로, double* 타입으로 캐스팅하여 pDouble에 저장합니다.

    *pInt = 10;
    *pDouble = 3.4;

    printf("정수형으로 사용 : %d\n", *pInt);
    printf("실수형으로 사용 : %.1lf\n", *pDouble);

    printf("%s : 0x%p\n",pLiteral, pLiteral);
    printf("%d 힙메모리 : 0x%p\n",*pInt, pInt);
    printf("%c 지역변수 : 0x%p\n",pLocalVariable, &pLocalVariable);
    printf("%s : 0x%p\n",pArray, pArray);

    free(pInt);
    free(pDouble);
    return 0;
}