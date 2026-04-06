//#pragma once //설명 : #pragma once는 헤더 파일이 여러 번 포함되는 것을 방지하는 전처리 지시자입니다.
#ifndef BASEBALL_H
#define BASEBALL_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#define SIZE 3

void generate_number(int* question);
void input_number(int* answer);
bool check_result(const int* question, const int* answer, int* strike, int* ball);
#endif
