#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int bookid;
    char bookname[40];
    char pulisher[40];
    int price;
}Book;

int main(void){
    int size;
    scanf("%d",&size);
    int *pArr;
    pArr = (int *)malloc(sizeof(int)*size); //malloc() 함수를 사용하여 int형 크기만큼 메모리를 동적으로 할당합니다. 반환된 포인터는 void* 타입이므로, int* 타입으로 캐스팅하여 pArr에 저장합니다.

    srand(time(NULL));
    for(int i=0;i<size;i++){
        *(pArr+i) = rand()%101;
    }
    for(int i=0;i<size;i++){
        printf("%d %p\n", *(pArr+i), pArr+i);
    }
    free(pArr);
    return 0;
}