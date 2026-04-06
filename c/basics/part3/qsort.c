#include<stdio.h>
#include<stdlib.h>

int compare(const void *a, const void *b); 

int main(void){

    int nums[10] = {40,20,52,23,47,36,98,47,37,21};
    int indexN = sizeof(nums)/sizeof(int);
    qsort(nums, indexN, sizeof(int), compare);
    
    for (int i =0 ;i<indexN;i++){
        printf("%d ",nums[i]);
    }
    printf("\n");
    return 0;
}

int compare(const void *a, const void *b){


    return (*(int *)a - *(int *)b);
}

