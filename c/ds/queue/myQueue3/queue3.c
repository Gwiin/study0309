#include "queue3.h"


int size(Qu *pq)
{
    return pq->size;
}

void initQueue(Qu *pq, int size, int eleSize)
{
    pq->pArr = malloc(eleSize * size);
    assert(pq->pArr != NULL);
    pq->eleSize = eleSize;
    pq->size = size;
    pq->front = pq->pArr;
    pq->rear = pq->pArr;
}


void cleanupQueue(Qu *pq)
{
    free(pq->pArr);
}


void push(Qu *pq, const void *pData)
{
    assert(pq->rear != (pq->pArr + pq->size));
    memcpy((unsigned char *)pq->rear, pData,pq->eleSize);
    pq->rear = (unsigned char *)pq->rear + pq->eleSize;
}


void pop(Qu *pq, void *pData)
{
    assert(pq->front != pq->rear);
    memcpy(pData, (unsigned char *)pq->front, pq->eleSize);
    pq->front = (unsigned char *)pq->front + pq->eleSize;
}

