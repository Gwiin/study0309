#include <stdio.h>

int main(){

    int score;
    printf("점수입력 : ");
    scanf("%d",&score);

    if (score >= 60)
    {
        printf("점수 : %d --- 합격\n",score);
    }
    else
    {
        printf("점수 : %d --- 탈락\n",score);
    }
    return 0;

}