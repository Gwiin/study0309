#include <stdio.h>

int main(void){
    int nums1[5] = {1,2,3,4,5};
    int nums2[] = {1,2,3,4,5}; //입력한 만큼의 메모리 확보
    int nums3[10] = {1,2,3,4,5}; //채워지지 않은 공간은 0으로 초기화
    int nums4[50]; //랜덤한 값이 채워져 있음
    int nums5[50] = {0}; //모든 값을 0으로 초기화, 효율성이 떨어짐


    int n = sizeof(nums5) / sizeof(int);
    for(int i=0;i<n;i++){
        printf("%d ",nums5[i]);
    }
    printf("\n");






    return 0;

}