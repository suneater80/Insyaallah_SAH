/*
#include <stdio.h>
#include <stdlib.h>
*/

#include "../header.h"

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int isFull(Queue *q) {
    return q->count == MAX_ANTRI;
}

int isEmpty(Queue *q) {
    return q->count == 0;
}

void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Antrian penuh!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_ANTRI;
    q->data[q->rear] = value;
    q->count++;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Antrian kosong!\n");
        return -1;
    }
    int value = q->data[q->front];
    q->front = (q->front + 1) % MAX_ANTRI;
    q->count--;
    return value;
}

int peek(Queue *q) {
    if (isEmpty(q)) return -1;
    return q->data[q->front];
}

int getCount(Queue *q) {
    return q->count;
}
