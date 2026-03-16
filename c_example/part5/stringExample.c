#include <stdio.h>
#include<string.h>

int main(void){
    char *ga = "asfsljflsialisjflsjfalisfj"; //문자열 리터럴 상수, 설명: 문자열 상수는 읽기 전용이므로, 포인터로 선언하여 문자열 상수를 가리키도록 하는 것이 좋습니다. 이렇게 하면 문자열 상수의 내용을 변경하려고 할 때 컴파일러가 오류를 발생시켜 안전성을 높일 수 있습니다. 또한, 문자열 상수는 프로그램의 데이터 영역에 저장되므로, 포인터로 접근하는 것이 메모리 효율성 측면에서도 유리합니다.
    char *str = "wonderful tonight";

    //strlen 함수
    int len = strlen(str);
    printf("len: %d \n",len);

    //strcpy 함수
    char str2[200];
    strcpy(str2, ga);
    strcpy(str2,str);
    for(int i=0;i<200;i++){
        printf("C%d: %c\n", i, str2[i]);
    }

    //strcmp 함수
    if(strcmp(str2,str)==0){
        printf("str과 str2는 같다.\n");
    }else{
        printf("str과 str2는 다르다.\n");
    }
    
    //strcat 함수
    char *str3 = "eric claption";
    strcat(str2," - ");
    strcat(str2, str3);
    printf("str2: %s\n",str2);

    return 0;


}