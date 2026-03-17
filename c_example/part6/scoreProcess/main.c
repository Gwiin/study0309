//구조체를 다뤄서 파일포인터로 저장, 읽어오기, 처리를 하는 프로그램

#include "scoreProcess.h"



int main(void){

    char *finpath = "/home/asd/0309/study/c_example/part6/scoreProcess/score.dat";
    char *foutpath = "/home/asd/0309/study/c_example/part6/scoreProcess/score.out";
    FILE *fin  = fopen(finpath,"r");
    FILE *fout = fopen(foutpath,"w");
    int n;

    printf("처리할 학생의 수를 입력하세요: ");
    if (scanf("%d",&n)!=1)
        return 1;

    if (fin == NULL || fout == NULL) 
    {
        fprintf(stderr, "파일을 열 수 없습니다.\n");
        return 1;
    }

    Sdata *students = (Sdata *)malloc(sizeof(Sdata) * n);
    Sdata **table = (Sdata **)malloc(sizeof(Sdata) * n);

    if(students == NULL || table == NULL)
    {
        fprintf(stderr, "메모리 할당에 실패\n");
        return 1;
    }


    inputData(fin, students, n);
    calculateScore(students, n);
    calculateRank(students, n);
    sortPointers(students, table, n);
    printResult(fout, table, n);
    
    fclose(fin);
    fclose(fout);
    return 0;

}



