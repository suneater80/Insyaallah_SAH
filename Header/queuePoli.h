#ifndef QUEUEPOLI_H
#define QUEUEPOLI_H

#include "../header.h"

#define MAX_ANTRI 7

typedef struct {
    int data[MAX_ANTRI];
    int front;
    int rear;
    int count;
} Queue;

void initQueue(Queue *q);
int isFull(Queue *q);
int isEmpty(Queue *q);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);
int peek(Queue *q);
int getCount(Queue *q);

#endif
