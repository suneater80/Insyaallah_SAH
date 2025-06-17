#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>  // Untuk fungsi input/output
#include <stdlib.h> // Untuk alokasi memori dinamis (jika diperlukan)
#include <string.h> // Untuk manipulasi string (jika diperlukan)

#define MAX_ANTRIAN_LAYANAN 24

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

// Fungsi untuk QueueLayanan
void initQueueLayanan(QueueLayanan *q);
int isFullLayanan(QueueLayanan *q);
int isEmptyLayanan(QueueLayanan *q);
int enqueueLayanan(QueueLayanan *q, Kategori kategori);
int dequeueLayanan(QueueLayanan *q);
AntrianLayanan* peekLayanan(QueueLayanan *q);
int getCountLayanan(QueueLayanan *q);





#define MAX_ANTRIAN_POLI 7 // Kapasitas maksimum antrian untuk satu poli
// ===== Struktur data queue untuk antrian poli =====
typedef struct {
    int data[MAX_ANTRIAN_POLI]; // Array untuk menyimpan nomor antrian
    int front; // Indeks elemen paling depan (dequeue)
    int rear; // Indeks elemen paling belakang (enqueue)
    int count; // Jumlah elemen dalam antrian
} QueuePoli;

// ==== FUNGSI & PROSEDUR POLI ====
void initQueuePoli(QueuePoli *q); // Inisialisasi queue
int isFullPoli(QueuePoli *q); // Cek apakah queue penuh
int isEmptyPoli(QueuePoli *q); // Cek apakah queue kosong
void enqueuePoli(QueuePoli *q, int value); // Tambah elemen ke queue
int dequeuePoli(QueuePoli *q); // Ambil elemen dari queue
int peekPoli(QueuePoli *q); // Lihat elemen paling depan queue
int getCountPoli(QueuePoli *q); // Ambil jumlah elemen dalam queue

#endif