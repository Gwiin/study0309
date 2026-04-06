#include <stdio.h>

char *myStrcpy(char *pDes, const char *pSrc);

int main(void){

    
    char str2[200]="strawberry";
    myStrcpy(str2, "apple");
    printf("str2: %s\n", str2);
    myStrcpy(str2,"banana");
    printf("str2: %s\n",str2);
    printf("str2: %s\n", myStrcpy(str2,"pineapple"));
    
    return 0;
}

char *myStrcpy(char *pDes, const char *pSrc){ 
// 함수명에 역참조 연산자(*)가 붙은 경우, 해당 함수는 포인터를 반환하는 함수임을 나타냅니다. 이 경우, myStrcpy 함수는 char* 타입의 포인터를 반환하는 함수입니다. 따라서, myStrcpy 함수는 문자열을 복사한 후에 복사된 문자열의 주소를 반환하는 역할을 합니다.
//함수의 인자는 char *pDes와 const char *pSrc입니다. pDes는 복사된 문자열이 저장될 버퍼의 주소를 나타내는 포인터이고, pSrc는 복사할 원본 문자열의 주소를 나타내는 포인터입니다. const 키워드는 pSrc가 가리키는 문자열이 변경되지 않도록 보장하는 역할을 합니다. 따라서, myStrcpy 함수는 pSrc에서 pDes로 문자열을 복사한 후에 pDes의 주소를 반환하는 함수입니다.

    char *pA = pDes; 
// *pA = pDes 와 *pA = *pDes는 다르다. *pA = pDes는 포인터 pA가 가리키는 위치에 pDes의 주소값을 저장하는 것이고, *pA = *pDes는 포인터 pA가 가리키는 위치에 pDes가 가리키는 위치의 값을 저장하는 것이다. 따라서, *pA = pDes는 포인터 pA가 가리키는 위치에 pDes의 주소값을 저장하는 것이고, *pA = *pDes는 포인터 pA가 가리키는 위치에 pDes가 가리키는 위치의 값을 저장하는 것이다.
    while(*pSrc != '\0')
    {
        *pDes = *pSrc;
        pDes++;
        pSrc++;
    }
    *pDes = '\0';
    return pA;

}


