#include "../Header/queue.h"

// ========== IMPLEMENTASI QUEUE LAYANAN ==========

void initQueueLayanan(QueueLayanan *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
    q->nomorCounter = 0;
}

int isFullLayanan(QueueLayanan *q) {
    return q->count >= MAX_ANTRIAN_LAYANAN;
}

int isEmptyLayanan(QueueLayanan *q) {
    return q->count == 0;
}

int enqueueLayanan(QueueLayanan *q, Kategori kategori) {
    if (isFullLayanan(q)) return 0;

    q->rear = (q->rear + 1) % MAX_ANTRIAN_LAYANAN;
    q->nomorCounter++;
    q->data[q->rear].nomor = q->nomorCounter;
    q->data[q->rear].kategori = kategori;
    q->count++;

    return 1;
}

int dequeueLayanan(QueueLayanan *q) {
    if (isEmptyLayanan(q)) return 0;

    int nomor = q->data[q->front].nomor;
    q->front = (q->front + 1) % MAX_ANTRIAN_LAYANAN;
    q->count--;

    return nomor;
}

AntrianLayanan* peekLayanan(QueueLayanan *q) {
    if (isEmptyLayanan(q)) return NULL;
    return &q->data[q->front];
}

int getCountLayanan(QueueLayanan *q) {
    return q->count;
}

// ========== IMPLEMENTASI QUEUE POLI ==========

void initQueuePoli(QueuePoli *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int isFullPoli(QueuePoli *q) {
    return q->count == MAX_ANTRIAN_POLI;
}

int isEmptyPoli(QueuePoli *q) {
    return q->count == 0;
}

void enqueuePoli(QueuePoli *q, int value) {
    if (isFullPoli(q)) {
        printf("Antrian penuh!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_ANTRIAN_POLI;
    q->data[q->rear] = value;
    q->count++;
}

int dequeuePoli(QueuePoli *q) {
    if (isEmptyPoli(q)) {
        printf("Antrian kosong!\n");
        return -1;
    }
    int value = q->data[q->front];
    q->front = (q->front + 1) % MAX_ANTRIAN_POLI;
    q->count--;
    return value;
}

int peekPoli(QueuePoli *q) {
    if (isEmptyPoli(q)) return -1;
    return q->data[q->front];
}

int getCountPoli(QueuePoli *q) {
    return q->count;
}