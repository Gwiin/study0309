#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    int lotto[6];
    int i,j;

    srand(time(NULL));

    for(i=0;i<6;i++){
        lotto[i] = (rand() % 45) + 1;
        //중복검사
        for(int j=0;j<i;j++){
            if(lotto[i] == lotto[j]){
                i--;
                break;
            }
        }
        printf("%d ",lotto[i]);
    }

    printf("\n");
    return 0;
}
