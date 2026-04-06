#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct{
    int *pArr;
    int *tos;
    int size;
}Stack;

void initStack(Stack *ps, int size);
void push(Stack *ps, int data);
int pop(Stack *ps);
void cleanupStack(Stack *ps);
int size(Stack *ps);