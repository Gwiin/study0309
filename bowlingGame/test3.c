#include <stdio.h>

#define MAX_ROLLS 21
#define FRAME_COUNT 10
#define NAME_LEN 20
#define MAX_PLAYERS 4

typedef struct {
    char p_name[NAME_LEN];
    int rolls[MAX_ROLLS];
    int roll_count;
    int frame_score[FRAME_COUNT];
    int sumscore[FRAME_COUNT];
} Bowl;

void init_score(Bowl *pb);
void put_score(Bowl *pb, int frame);
void calc_score(Bowl *pb);
void print_score(Bowl *pb);

void input_players(Bowl players[], int player_count);
void play_game(Bowl players[], int player_count);
void print_all_scores(Bowl players[], int player_count);
void print_menu(void);

int main(void)
{
    Bowl players[MAX_PLAYERS];
    int player_count;
    int menu;

    while (1)
    {
        print_menu();
        printf("메뉴 선택: ");
        scanf("%d", &menu);

        if (menu == 1)
        {
            player_count = 0;

            printf("플레이어 수 입력: ");
            scanf("%d", &player_count);

            if (player_count <= 0)
            {
                printf("플레이어 수는 1명 이상이어야 합니다.\n");
                continue;
            }

            if (player_count > MAX_PLAYERS)
            {
                printf("최대 플레이어 수는 %d명입니다.\n", MAX_PLAYERS);
                continue;
            }

            input_players(players, player_count);
            play_game(players, player_count);
        }
        else if (menu == 2)
        {
            printf("게임을 종료합니다.\n");
            break;
        }
        else
        {
            printf("올바른 메뉴를 선택하세요.\n");
        }
    }

    return 0;
}

void print_menu(void)
{
    printf("\n=========================\n");
    printf("       볼링 게임 메뉴\n");
    printf("=========================\n");
    printf("1. 게임 시작\n");
    printf("2. 게임 종료\n");
    printf("=========================\n");
}

void input_players(Bowl players[], int player_count)
{
    for (int i = 0; i < player_count; i++)
    {
        printf("플레이어 %d 이름 입력: ", i + 1);
        scanf("%19s", players[i].p_name);
        init_score(&players[i]);
    }
}

void play_game(Bowl players[], int player_count)
{
    for (int frame = 1; frame <= FRAME_COUNT; frame++)
    {
        for (int i = 0; i < player_count; i++)
        {
            print_all_scores(players, player_count);

            printf("\n현재 플레이어: %s\n", players[i].p_name);
            printf("현재 프레임: %d\n", frame);

            put_score(&players[i], frame);
            calc_score(&players[i]);
        }
    }

    printf("\n==================== 최종 결과 ====================\n");
    print_all_scores(players, player_count);
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

            if (pb->rolls[roll_idx] + pb->rolls[roll_idx + 1] == 10)
            {
                if (frame < 9)
                {
                    if (roll_idx + 2 >= pb->roll_count)
                        break;

                    pb->frame_score[frame] = 10 + pb->rolls[roll_idx + 2];
                }
                else
                {
                    pb->frame_score[frame] =
                        pb->rolls[roll_idx] + pb->rolls[roll_idx + 1];

                    if (roll_idx + 2 < pb->roll_count)
                        pb->frame_score[frame] += pb->rolls[roll_idx + 2];
                }
            }
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

    printf("--------------------------------------------------------\n");
}

void print_all_scores(Bowl players[], int player_count)
{
    printf("\n========================================================\n");
    printf("| Player     | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10  |\n");
    printf("========================================================\n");

    for (int p = 0; p < player_count; p++)
    {
        int roll_idx = 0;

        /* 첫 줄: 이름 + 투구 점수 */
        printf("| %-10s |", players[p].p_name);

        for (int frame = 0; frame < 9; frame++)
        {
            char c1 = ' ';
            char c2 = ' ';

            if (roll_idx < players[p].roll_count)
            {
                if (players[p].rolls[roll_idx] == 10)
                {
                    c1 = ' ';
                    c2 = 'X';
                    roll_idx += 1;
                }
                else
                {
                    int first = players[p].rolls[roll_idx];
                    c1 = (first == 0) ? '-' : ('0' + first);

                    if (roll_idx + 1 < players[p].roll_count)
                    {
                        int second = players[p].rolls[roll_idx + 1];

                        if (first + second == 10)
                            c2 = '/';
                        else
                            c2 = (second == 0) ? '-' : ('0' + second);
                    }

                    roll_idx += 2;
                }
            }

            printf("%c|%c|", c1, c2);
        }

        /* 10프레임 */
        {
            char c1 = ' ';
            char c2 = ' ';
            char c3 = ' ';

            if (roll_idx < players[p].roll_count)
            {
                int first = players[p].rolls[roll_idx];

                if (first == 10) c1 = 'X';
                else if (first == 0) c1 = '-';
                else c1 = '0' + first;

                if (roll_idx + 1 < players[p].roll_count)
                {
                    int second = players[p].rolls[roll_idx + 1];

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

                    if (roll_idx + 2 < players[p].roll_count)
                    {
                        int third = players[p].rolls[roll_idx + 2];

                        if (third == 10) c3 = 'X';
                        else if (third == 0) c3 = '-';
                        else c3 = '0' + third;
                    }
                }
            }

            printf("%c|%c|%c|\n", c1, c2, c3);
        }

        /* 둘째 줄: 누적 점수 */
        printf("|            |");

        for (int i = 0; i < 9; i++)
        {
            if (players[p].sumscore[i] == 0)
                printf("   |");
            else
                printf("%3d|", players[p].sumscore[i]);
        }

        if (players[p].sumscore[9] == 0)
            printf("     |\n");
        else
            printf("%5d|\n", players[p].sumscore[9]);

        printf("--------------------------------------------------------\n");
    }
}