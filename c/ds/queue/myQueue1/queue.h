#pragma once

#include <stdio.h>
#include <stdlib.h>
#define QUEUESIZE 100

typedef struct {
    int queue[QUEUESIZE];
    int *front;
    int *rear;
}Queue;

// front와 rear를 포인터로 선언한 이유 : 

void initQueue(Queue *pq);
void push(Queue *pq, int data);
int pop(Queue *pq);
void cleanQueue(Queue *pq);