#ifndef QUEUE_H
#define QUEUE_H

#define MAX_ANTRIAN 20

// Kategori pasien
typedef enum {
    UMUM,
    BPJS
} Kategori;

// Struct data antrian
typedef struct {
    int nomor;            // Nomor antrian
    Kategori kategori;    // Kategori pasien
} Antrian;

// Queue untuk antrian
typedef struct {
    Antrian data[MAX_ANTRIAN];
    int front;
    int rear;
    int count;
} Queue;

// Inisialisasi queue
void initQueue(Queue *q);

// Cek apakah queue penuh
int isFull(Queue *q);

// Cek apakah queue kosong
int isEmpty(Queue *q);

// Tambah antrian ke queue
int enqueue(Queue *q, Kategori kategori);

// Ambil antrian dari queue (digunakan untuk "dipanggil")
int dequeue(Queue *q);

// Lihat antrian paling depan
Antrian* peek(Queue *q);

#endif
