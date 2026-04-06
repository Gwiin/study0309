#include <stdio.h>

int main(){
    int num;
    printf("숫자입력: ");
    scanf("%d",&num);
    // if(num<0){
    //     num= -num;
    // }

    printf("절대값은 : %d\n",num<0 ? -num:num); //삼항연산자를 사용하면 if문보다 짧아질수는 있지만 가독성이 떨어진다.
    return 0;
}