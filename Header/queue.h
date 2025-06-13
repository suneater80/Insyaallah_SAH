#ifndef QUEUE_H
#define QUEUE_H

#include "../header.h"

#define MAKS_ANTRIAN 20

typedef struct {
    int nomor;
} Antrian;

typedef struct {
    Antrian queue[MAKS_ANTRIAN];
    int depan, belakang;
} Queue;

void initQueue(Queue *q);
int isFull(Queue *q);
int isEmpty(Queue *q);
void enqueue(Queue *q);
int dequeue(Queue *q);
int lihatDepan(Queue *q);
void tampilAntrian(Queue *q);

// Fungsi CLI
void ambilAntrianLayanan(Queue *q);
void lihatAntrianLayanan(Queue *q);

#endif
