#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ANTRIAN_LAYANAN 20
#define MAX_ANTRIAN_POLI 7

// Kategori pasien untuk layanan
typedef enum {
    UMUM,
    BPJS
} Kategori;

// Struct data antrian layanan
typedef struct {
    int nomor;            // Nomor antrian
    Kategori kategori;    // Kategori pasien
} AntrianLayanan;

// Queue untuk antrian layanan
typedef struct {
    AntrianLayanan data[MAX_ANTRIAN_LAYANAN];
    int front;
    int rear;
    int count;
    int nomorCounter;     // Counter untuk nomor antrian
} QueueLayanan;

// Queue untuk antrian poli (integer sederhana)
typedef struct {
    int data[MAX_ANTRIAN_POLI];
    int front;
    int rear;
    int count;
} QueuePoli;

// Fungsi untuk QueueLayanan
void initQueueLayanan(QueueLayanan *q);
int isFullLayanan(QueueLayanan *q);
int isEmptyLayanan(QueueLayanan *q);
int enqueueLayanan(QueueLayanan *q, Kategori kategori);
int dequeueLayanan(QueueLayanan *q);
AntrianLayanan* peekLayanan(QueueLayanan *q);
int getCountLayanan(QueueLayanan *q);

// Fungsi untuk QueuePoli
void initQueuePoli(QueuePoli *q);
int isFullPoli(QueuePoli *q);
int isEmptyPoli(QueuePoli *q);
void enqueuePoli(QueuePoli *q, int value);
int dequeuePoli(QueuePoli *q);
int peekPoli(QueuePoli *q);
int getCountPoli(QueuePoli *q);

#endif