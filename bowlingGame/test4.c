#include <stdio.h>
#include <time.h>

#define MAX_ROLLS 21
#define FRAME_COUNT 10
#define NAME_LEN 20
#define MAX_PLAYERS 4
#define RECORD_FILE "/home/asd/0309/study/bowlingGame/bowlingscore.dat"
#define RECORD_HEADER "==================== GAME RECORD ====================\n"

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

void print_menu(void);
void show_rules(void);

void input_players(Bowl players[], int player_count);
void play_game(Bowl players[], int player_count);

void write_scoreboard(FILE *fp, Bowl players[], int player_count);
void print_all_scores(Bowl players[], int player_count);
void save_scoreboard(Bowl players[], int player_count);

void show_all_game_records(void);
void show_last_game_record(void);

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

        switch (menu)
        {
            case 1:
                printf("플레이어 수 입력 (최대 %d명): ", MAX_PLAYERS);
                scanf("%d", &player_count);

                if (player_count < 1 || player_count > MAX_PLAYERS)
                {
                    printf("플레이어 수는 1명 이상 %d명 이하여야 합니다.\n", MAX_PLAYERS);
                    break;
                }

                input_players(players, player_count);
                play_game(players, player_count);
                break;

            case 2:
                show_last_game_record();
                break;

            case 3:
                show_all_game_records();
                break;

            case 4:
                show_rules();
                break;

            case 5:
                printf("프로그램을 종료합니다.\n");
                return 0;

            default:
                printf("올바른 메뉴를 선택하세요.\n");
        }
    }

    return 0;
}

void print_menu(void)
{
    printf("\n=========================\n");
    printf("      볼링 게임 메뉴\n");
    printf("=========================\n");
    printf("1. 게임 시작\n");
    printf("2. 이전 게임 기록\n");
    printf("3. 모든 게임 기록\n");
    printf("4. 규칙 설명\n");
    printf("5. 종료\n");
    printf("=========================\n");
}

void show_rules(void)
{
    printf("\n==================== 규칙 설명 ====================\n");
    printf("1. 볼링은 총 10프레임으로 진행됩니다.\n");
    printf("2. 1~9프레임은 최대 2번 투구합니다.\n");
    printf("3. 첫 번째 투구가 10점이면 스트라이크(X)이며 해당 프레임은 종료됩니다.\n");
    printf("4. 두 번의 투구 합이 10점이면 스페어(/)입니다.\n");
    printf("5. 10프레임에서는 스트라이크 또는 스페어일 경우 1번 더 투구할 수 있습니다.\n");
    printf("6. 스트라이크는 다음 2번의 투구 점수를 보너스로 받습니다.\n");
    printf("7. 스페어는 다음 1번의 투구 점수를 보너스로 받습니다.\n");
    printf("===================================================\n");
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
            printf("\n현재 플레이어: %s\n", players[i].p_name);
            printf("현재 프레임: %d\n", frame);
            print_all_scores(players, player_count);

            put_score(&players[i], frame);
            calc_score(&players[i]);
        }
    }

    printf("\n==================== 최종 결과 ====================\n");
    print_all_scores(players, player_count);

    save_scoreboard(players, player_count);
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

void write_scoreboard(FILE *fp, Bowl players[], int player_count)
{
    fprintf(fp, "========================================================\n");
    fprintf(fp, "| Player     | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10  |\n");
    fprintf(fp, "========================================================\n");

    for (int p = 0; p < player_count; p++)
    {
        int roll_idx = 0;

        fprintf(fp, "| %-10s |", players[p].p_name);

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

            fprintf(fp, "%c|%c|", c1, c2);
        }

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

            fprintf(fp, "%c|%c|%c|\n", c1, c2, c3);
        }

        fprintf(fp, "|            |");

        for (int i = 0; i < 9; i++)
        {
            if (players[p].sumscore[i] == 0)
                fprintf(fp, "   |");
            else
                fprintf(fp, "%3d|", players[p].sumscore[i]);
        }

        if (players[p].sumscore[9] == 0)
            fprintf(fp, "     |\n");
        else
            fprintf(fp, "%5d|\n", players[p].sumscore[9]);

        fprintf(fp, "--------------------------------------------------------\n");
    }
}

void print_all_scores(Bowl players[], int player_count)
{
    write_scoreboard(stdout, players, player_count);
}

void save_scoreboard(Bowl players[], int player_count)
{
    FILE *fp = fopen(RECORD_FILE, "a");
    if (fp == NULL)
    {
        printf("기록 파일을 열 수 없습니다.\n");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char time_str[30];

    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", t);

    fprintf(fp, "\n%s", RECORD_HEADER);
    fprintf(fp, "End Time : %s\n\n", time_str);

    write_scoreboard(fp, players, player_count);

    fprintf(fp, "=====================================================\n\n");

    fclose(fp);

    printf("게임 기록이 %s 파일에 저장되었습니다.\n", RECORD_FILE);
}

void show_all_game_records(void)
{
    FILE *fp = fopen(RECORD_FILE, "r");
    if (fp == NULL)
    {
        printf("저장된 게임 기록이 없습니다.\n");
        return;
    }

    char ch;

    printf("\n==================== 모든 게임 기록 ====================\n");
    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }
    printf("========================================================\n");

    fclose(fp);
}

void show_last_game_record(void)
{
    FILE *fp = fopen(RECORD_FILE, "r");
    if (fp == NULL)
    {
        printf("저장된 게임 기록이 없습니다.\n");
        return;
    }

    long last_pos = 0;
    long current_pos;
    char line[512];

    while (1)
    {
        current_pos = ftell(fp);

        if (fgets(line, sizeof(line), fp) == NULL)
            break;

        int matched = 1;
        for (int i = 0; RECORD_HEADER[i] != '\0'; i++)
        {
            if (line[i] != RECORD_HEADER[i])
            {
                matched = 0;
                break;
            }
        }

        if (matched)
            last_pos = current_pos;
    }

    fseek(fp, last_pos, SEEK_SET);

    printf("\n==================== 이전 게임 기록 ====================\n");
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }
    printf("========================================================\n");

    fclose(fp);
}