#include <stdio.h>

int main(void){
    int num;
    printf("숫자입력: ");
    scanf("%d",&num);

    if(num>0){
        printf("%d는 양수\n",num);
    }else if(num==0){
        printf("%d는 0\n",num);
    }else{
        printf("%d는 음수\n",num);
    }
    return 0;

}