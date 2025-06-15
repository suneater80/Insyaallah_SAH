#include "../Header/queue.h"
#include <stdio.h>

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int isFull(Queue *q) {
    return q->count >= MAX_ANTRIAN;
}

int isEmpty(Queue *q) {
    return q->count == 0;
}

int enqueue(Queue *q, Kategori kategori) {
    if (isFull(q)) return 0;

    q->rear = (q->rear + 1) % MAX_ANTRIAN;
    q->data[q->rear].nomor = q->count + 1;
    q->data[q->rear].kategori = kategori;
    q->count++;

    return 1;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) return 0;

    q->front = (q->front + 1) % MAX_ANTRIAN;
    q->count--;

    return 1;
}

Antrian* peek(Queue *q) {
    if (isEmpty(q)) return NULL;
    return &q->data[q->front];
}

int getCount(Queue *q) {
    return q->count;
}