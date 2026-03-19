#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


typedef struct {
    void *pArr;
    int eleSize;
    int size;
    void *front;
    void *rear;
}Qu;

void initQueue(Qu *pq, int eleSize, int size);
void cleanupQueue(Qu *pq);
void push(Qu *pq, const void *pData);
void pop(Qu *pq, void *pData);
int size(Qu *pq);