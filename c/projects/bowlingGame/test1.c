#include <stdio.h>

#define FRAME_COUNT 10

typedef struct{

    char p_name[20];
    int score[FRAME_COUNT];
    int sumscore[FRAME_COUNT];
    int first[FRAME_COUNT];
    int second[FRAME_COUNT];
    int third;
    int frame;

}Bowl;

void init_score(Bowl *pb);
void put_score(Bowl *pb);
void print_score(Bowl *pb);
void calc_score(Bowl *pb);

int main(void)
{
    Bowl b1;

    printf("Enter player name: ");
    scanf("%s", b1.p_name);
    init_score(&b1);

    for(int i=0; i<10 ; i++)
    {
        print_score(&b1);
        put_score(&b1);
        calc_score(&b1);
    }
    print_score(&b1);
    return 0;
}

void init_score(Bowl *pb)
{
    pb->frame = 1;
    pb->third = 0;
    for(int i=0; i<11; i++)
    {
        pb->score[i] = 0;
        pb->sumscore[i] = 0;
        pb->first[i] = 0;
        pb->second[i] = 0;
    }
}


void put_score(Bowl *pb)
{
    int idx = pb->frame - 1;

    if(pb->frame <= 9)
    {
        printf("%d frame 1 try: ", pb->frame);
        scanf("%d", &pb->first[idx]);

        if(pb->first[idx] != 10)
        {
            printf("%d frame 2 try: ", pb->frame);
            scanf("%d", &pb->second[idx]);
        }
    }
    else if(pb->frame == 10)
    {
        printf("%d frame 1 try: ", pb->frame);
        scanf("%d", &pb->first[idx]);

        printf("%d frame 2 try: ", pb->frame);
        scanf("%d", &pb->second[idx]);

        if(pb->first[idx] == 10 || pb->first[idx] + pb->second[idx] == 10)
        {
            printf("%d frame 3 try: ", pb->frame);
            scanf("%d", &pb->third);
        }
    }

    pb->frame++;
}


void calc_score(Bowl *pb)
{
    int total = 0;
    int current_frame = pb->frame - 1;   // 현재까지 입력 완료된 프레임 수

    for (int i = 0; i < 10; i++)
    {
        pb->score[i] = 0;
        pb->sumscore[i] = 0;
    }

    for (int i = 0; i < current_frame; i++)
    {
        if (i < 9)
        {
            /* strike */
            if (pb->first[i] == 10)
            {
                if (i + 1 >= current_frame)
                    break;   // 다음 프레임 입력 전이면 아직 점수 확정 불가

                if (i == 8)
                {
                    pb->score[i] = 10 + pb->first[9] + pb->second[9];
                }
                else
                {
                    if (pb->first[i + 1] == 10)
                    {
                        if (i + 2 >= current_frame)
                            break;   // 다음다음 프레임 필요

                        pb->score[i] = 10 + 10 + pb->first[i + 2];
                    }
                    else
                    {
                        pb->score[i] = 10 + pb->first[i + 1] + pb->second[i + 1];
                    }
                }
            }
            /* spare */
            else if (pb->first[i] + pb->second[i] == 10)
            {
                if (i + 1 >= current_frame)
                    break;   // 다음 프레임 첫 투구가 있어야 확정 가능

                pb->score[i] = 10 + pb->first[i + 1];
            }
            /* open frame */
            else
            {
                pb->score[i] = pb->first[i] + pb->second[i];
            }
        }
        else
        {
            /* 10th frame */
            pb->score[i] = pb->first[i] + pb->second[i] + pb->third;
        }

        total += pb->score[i];
        pb->sumscore[i] = total;
    }
}



void print_score(Bowl *pb)
{
    printf("\nPlayer name: %s\n", pb->p_name);
    printf("-------------------------------------------\n");
    printf("| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10  |\n");
    printf("-------------------------------------------\n");

    /* 점수 표시 줄 */
    for (int i = 0; i < 9; i++)
    {
        char c1 = ' ';
        char c2 = ' ';

        if (pb->first[i] == 10)
        {
            c1 = ' ';
            c2 = 'X';
        }
        else
        {
            if (pb->first[i] == 0 && pb->second[i] == 0)
            {
                c1 = ' ';
                c2 = ' ';
            }
            else
            {
                if (pb->first[i] == 0) c1 = '-';
                else c1 = '0' + pb->first[i];

                if (pb->first[i] + pb->second[i] == 10)
                    c2 = '/';
                else if (pb->second[i] == 0)
                    c2 = '-';
                else
                    c2 = '0' + pb->second[i];
            }
        }

        printf("|%c|%c", c1, c2);
    }

    /* 10프레임 */
    {
        char c1 = ' ';
        char c2 = ' ';
        char c3 = ' ';

        if (pb->first[9] == 10) c1 = 'X';
        else if (pb->first[9] == 0) c1 = '-';
        else if (pb->first[9] != 0) c1 = '0' + pb->first[9];

        if (pb->first[9] == 10)
        {
            if (pb->second[9] == 10) c2 = 'X';
            else if (pb->second[9] == 0) c2 = '-';
            else c2 = '0' + pb->second[9];
        }
        else
        {
            if (pb->first[9] + pb->second[9] == 10) c2 = '/';
            else if (pb->second[9] == 0) c2 = '-';
            else if (pb->second[9] != 0) c2 = '0' + pb->second[9];
        }

        if (pb->first[9] == 10 || pb->first[9] + pb->second[9] == 10)
        {
            if (pb->third == 10) c3 = 'X';
            else if (pb->third == 0) c3 = '-';
            else if (pb->third != 0) c3 = '0' + pb->third;
        }

        printf("|%c|%c|%c|\n", c1, c2, c3);
    }

    printf("-------------------------------------------\n");

    /* 누적 점수 줄 */
    for (int i = 0; i < 9; i++)
    {
        if (pb->sumscore[i] == 0)
            printf("|   ");
        else
            printf("|%3d", pb->sumscore[i]);
    }

    if (pb->sumscore[9] == 0)
        printf("|     |\n");
    else
        printf("|%5d|\n", pb->sumscore[9]);

    printf("-------------------------------------------\n");
}