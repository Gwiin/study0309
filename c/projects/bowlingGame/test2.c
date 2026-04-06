#include <stdio.h>

#define MAX_ROLLS 21
#define FRAME_COUNT 10
#define NAME_LEN 20

typedef struct {
    char p_name[NAME_LEN];
    int rolls[MAX_ROLLS];      // 모든 투구를 순서대로 저장
    int roll_count;            // 현재까지 저장된 투구 개수
    int frame_score[FRAME_COUNT];
    int sumscore[FRAME_COUNT];
} Bowl;

void init_score(Bowl *pb);
void put_score(Bowl *pb, int frame);
void calc_score(Bowl *pb);
void print_score(Bowl *pb);

int main(void)
{
    Bowl b1;

    printf("Enter player name: ");
    scanf("%19s", b1.p_name);

    init_score(&b1);

    for (int frame = 1; frame <= FRAME_COUNT; frame++)
    {
        print_score(&b1);
        put_score(&b1, frame);
        calc_score(&b1);
    }

    print_score(&b1);

    return 0;
}

void init_score(Bowl *pb)
{
    pb->roll_count = 0;

    for (int i = 0; i < MAX_ROLLS; i++)
        pb->rolls[i] = 0;

    for (int i = 0; i < FRAME_COUNT; i++)
    {
        pb->frame_score[i] = 0;
        pb->sumscore[i] = 0;
    }
}

void put_score(Bowl *pb, int frame)
{
    int first, second, third;

    if (frame <= 9)
    {
        printf("%d frame 1 try: ", frame);
        scanf("%d", &first);
        pb->rolls[pb->roll_count++] = first;

        if (first != 10)
        {
            printf("%d frame 2 try: ", frame);
            scanf("%d", &second);
            pb->rolls[pb->roll_count++] = second;
        }
    }
    else
    {
        printf("%d frame 1 try: ", frame);
        scanf("%d", &first);
        pb->rolls[pb->roll_count++] = first;

        printf("%d frame 2 try: ", frame);
        scanf("%d", &second);
        pb->rolls[pb->roll_count++] = second;

        if (first == 10 || first + second == 10)
        {
            printf("%d frame 3 try: ", frame);
            scanf("%d", &third);
            pb->rolls[pb->roll_count++] = third;
        }
    }
}

void calc_score(Bowl *pb)
{
    int roll_idx = 0;
    int total = 0;

    for (int i = 0; i < FRAME_COUNT; i++)
    {
        pb->frame_score[i] = 0;
        pb->sumscore[i] = 0;
    }

    for (int frame = 0; frame < FRAME_COUNT; frame++)
    {
        if (roll_idx >= pb->roll_count)
            break;

        /* strike */
        if (pb->rolls[roll_idx] == 10)
        {
            if (frame < 9)
            {
                if (roll_idx + 2 >= pb->roll_count)
                    break;

                pb->frame_score[frame] =
                    10 + pb->rolls[roll_idx + 1] + pb->rolls[roll_idx + 2];
                total += pb->frame_score[frame];
                pb->sumscore[frame] = total;
                roll_idx += 1;
            }
            else
            {
                if (roll_idx + 1 >= pb->roll_count)
                    break;

                pb->frame_score[frame] = pb->rolls[roll_idx];
                pb->frame_score[frame] += pb->rolls[roll_idx + 1];

                if (roll_idx + 2 < pb->roll_count)
                    pb->frame_score[frame] += pb->rolls[roll_idx + 2];

                total += pb->frame_score[frame];
                pb->sumscore[frame] = total;
                break;
            }
        }
        else
        {
            if (roll_idx + 1 >= pb->roll_count)
                break;

            /* spare */
            if (pb->rolls[roll_idx] + pb->rolls[roll_idx + 1] == 10)
            {
                if (frame < 9)
                {
                    if (roll_idx + 2 >= pb->roll_count)
                        break;

                    pb->frame_score[frame] =
                        10 + pb->rolls[roll_idx + 2];
                }
                else
                {
                    pb->frame_score[frame] =
                        pb->rolls[roll_idx] + pb->rolls[roll_idx + 1];

                    if (roll_idx + 2 < pb->roll_count)
                        pb->frame_score[frame] += pb->rolls[roll_idx + 2];
                }
            }
            /* open frame */
            else
            {
                pb->frame_score[frame] =
                    pb->rolls[roll_idx] + pb->rolls[roll_idx + 1];
            }

            total += pb->frame_score[frame];
            pb->sumscore[frame] = total;
            roll_idx += 2;
        }
    }
}

void print_score(Bowl *pb)
{
    int roll_idx = 0;

    printf("\nPlayer name: %s\n", pb->p_name);
    printf("-------------------------------------------\n");
    printf("| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10  |\n");
    printf("-------------------------------------------\n");

    for (int frame = 0; frame < 9; frame++)
    {
        char c1 = ' ';
        char c2 = ' ';

        if (roll_idx < pb->roll_count)
        {
            if (pb->rolls[roll_idx] == 10)
            {
                c1 = ' ';
                c2 = 'X';
                roll_idx += 1;
            }
            else
            {
                int first = pb->rolls[roll_idx];
                c1 = (first == 0) ? '-' : ('0' + first);

                if (roll_idx + 1 < pb->roll_count)
                {
                    int second = pb->rolls[roll_idx + 1];

                    if (first + second == 10)
                        c2 = '/';
                    else
                        c2 = (second == 0) ? '-' : ('0' + second);
                }

                roll_idx += 2;
            }
        }

        printf("|%c|%c", c1, c2);
    }

    /* 10프레임 */
    {
        char c1 = ' ';
        char c2 = ' ';
        char c3 = ' ';

        if (roll_idx < pb->roll_count)
        {
            int first = pb->rolls[roll_idx];

            if (first == 10) c1 = 'X';
            else if (first == 0) c1 = '-';
            else c1 = '0' + first;

            if (roll_idx + 1 < pb->roll_count)
            {
                int second = pb->rolls[roll_idx + 1];

                if (first == 10)
                {
                    if (second == 10) c2 = 'X';
                    else if (second == 0) c2 = '-';
                    else c2 = '0' + second;
                }
                else
                {
                    if (first + second == 10) c2 = '/';
                    else if (second == 0) c2 = '-';
                    else c2 = '0' + second;
                }

                if (roll_idx + 2 < pb->roll_count)
                {
                    int third = pb->rolls[roll_idx + 2];

                    if (third == 10) c3 = 'X';
                    else if (third == 0) c3 = '-';
                    else c3 = '0' + third;
                }
            }
        }

        printf("|%c|%c|%c|\n", c1, c2, c3);
    }

    printf("-------------------------------------------\n");

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