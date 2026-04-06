#include "bowling.h"


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