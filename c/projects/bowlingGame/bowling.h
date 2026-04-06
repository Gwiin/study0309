#pragma once
#include <stdio.h>
#include <time.h>

#define MAX_ROLLS 21
#define FRAME_COUNT 10
#define NAME_LEN 20
#define MAX_PLAYERS 4
#define RECORD_FILE "/home/asd/study/c/projects/bowlingGame/bowlingscore.dat"
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
