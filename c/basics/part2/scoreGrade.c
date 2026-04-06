#include <stdio.h>

int main(){

    int score;
    char grade = 'F';
    printf("점수입력 : ");
    scanf("%d",&score);

    if(score >= 90){
        grade = 'A';
    }else if(score >= 80){
        grade = 'B';
    }else if(score >= 70){
        grade = 'C';
    }else if(score >= 60){
        grade = 'D';
    }

    printf("%d점은 %c 입니다.\n",score,grade);
    return 0;

}