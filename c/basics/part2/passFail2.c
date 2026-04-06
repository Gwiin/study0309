#include <stdio.h>
#include <stdlib.h> // atoi 함수 (array to int : array를 int로 치환)

int main(int argc, char *argv[]) // argc -> argument count (인자 개수) | argv -> argument vector (인자 벡터)
{   
    // int score;
    // printf("점수입력 : ");
    // scanf("%d",&score);

    int score = atoi(argv[1]); // atoi 함수는 문자열을 정수로 변환하는 함수입니다. argv[1]은 명령줄에서 입력된 첫 번째 인자를 나타냅니다. 예를 들어, 프로그램을 실행할 때 "program 85"와 같이 입력하면 argv[1]은 "85"가 되고, atoi(argv[1])은 85라는 정수로 변환됩니다.
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

//Segmentation fault (core dumped) -> 배열 -1 까지만 접근을 해야함 그렇지 않아서 발생한 에러