#include <stdio.h>


void swap(int *a, int *b);

int main(void){

    int nums[10] = {40,20,52,23,47,36,98,47,37,21};

    int indexN = sizeof(nums)/sizeof(int);
    for(int i=0 ; i < indexN ; i++){
        for(int j=i+1 ; j < indexN ; j++){
            if(nums[i]>nums[j]){
                swap(&nums[i],&nums[j]);
            
            }
        }
    }
    for (int i =0 ;i<indexN;i++){
        printf("%d ",nums[i]);
    }
    printf("\n");
    return 0;

}


void swap(int *a, int *b){

    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}


