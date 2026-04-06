#include <stdio.h>
#include <string.h>

int main(void){

    char string1[100];

    printf("문자열을 넣으시오 : \n");
    //gets -> NULL 이 있을때 까지 받음, 지금은 쓰이지 않는다.
    //gets();
    fgets(string1, 10,stdin); 
    printf("%s",string1);
    printf("문자열 입력 : \n");
    scanf("%s",string1);
    // fscanf(stdin, "%s",string1);
    printf("%s",string1);
    scanf("%s",string1);
    printf("%s",string1);
    return 0;
}