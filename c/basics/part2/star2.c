#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//피라미드 형태 출력 이중 for문 사용



int main(void){

    system("clear"); //리눅스 명령어 사용가능

    int height;
    printf("몇층: ");
    scanf("%d",&height);
    
    for(int i=1;i<=height;i++){
        for(int j=1;j<=height-i;j++){
            printf(" ");
        }
        for(int k=0;k<i*2-1;k++){
            printf("*");
        }
        sleep(1);
        printf("\n");
    }

    return 0;
}