#include<stdio.h>

int main(void){

    for(int i=1;i<=5;i++){
        for(int j=1;j<i;j++){
            // if(i+j == 6 || i==j){
            //     printf("*");
            // }else{
            //     printf(" ");
            // } 
            printf((i+j ==6 || i==j)?"*":" "); 
        }
        printf("\n");
    }

    return 0;
}

