#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXINDEX 30

int main(){

    int nums[MAXINDEX];

    srand(time(NULL));
    for(int i=0;i<MAXINDEX ; i++){
        nums[i] = rand() % 1000;
        printf("%d ",nums[i]);
    }
    printf("\n");
    
    int max;
    max = nums[0];
    for(int i=0; i < MAXINDEX ; i++){
        if (max < nums[i]){
            max = nums[i];
        }
    }
    printf("최대값: %d\n",max);
    return 0;
}
