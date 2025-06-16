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

// MODUL QUEUE POLI (KOSONG)
void initQueuePoli(QueuePoli *q) {
    q->front = 0; // Indeks elemen pertama
    q->rear = -1; // Indeks elemen terakhir
    q->count = 0;  // Jumlah elemen dalam queue (antrian)
}



// MODUL CEK APAKAH QUEUE PENUH 
int isFullPoli(QueuePoli *q) {
    return q->count == MAX_ANTRIAN_POLI; // Return 1 jika penuh, 0 jika tidak
}



// MODUL APAKAH QUEUE KOSONG 
int isEmptyPoli(QueuePoli *q) {
    return q->count == 0; // Return 1 jika kosong, 0 jika tidak
}



// TAMBAHKAN ELEMEN KE BELAKANG QUEUE
void enqueuePoli(QueuePoli *q, int value) {
    if (isFullPoli(q)) {
        printf("Antrian penuh!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_ANTRIAN_POLI; // Circular queue: looping kembali ke awal jika sudah mentok
    q->data[q->rear] = value;  // Simpan nomor antrian pasien
    q->count++; // Tambah jumlah elemen
}



// MODUL MENGELUARKAN ELEMEN DARI DEPAN QUEUE 
int dequeuePoli(QueuePoli *q) {
    if (isEmptyPoli(q)) {
        printf("Antrian kosong!\n");
        return -1; // Return -1 jika kosong
    }
    int value = q->data[q->front];  // Ambil data paling depan
    q->front = (q->front + 1) % MAX_ANTRIAN_POLI; // Circular queue
    q->count--;  // Kurangi jumlah elemen
    return value; // Return data yang diambil
}



// MODUL MENGAMBIL ELEMEN PALING DEPAN TANPA MENGHAPUS 
int peekPoli(QueuePoli *q) {
    if (isEmptyPoli(q)) return -1; // Jika kosong, return -1
    return q->data[q->front]; // Return elemen paling depan
}



// MODUL MENGAMBIL JUMLAH ELEMEN SAAT DALAM QUEUE
int getCountPoli(QueuePoli *q) {
    return q->count;  // Return jumlah elemen dalam queue
}