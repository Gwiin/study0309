#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

    int nums[10];
    int sum=0;
    srand(time(NULL));
    

    for(int i=0;i<10;i++){
        nums[i] = rand() % 100;
        sum += nums[i];
        printf("%d ",nums[i]);

    }
    printf("\nsum = %d\n",sum);

    return 0;
}