/*modul untuk antrian dan layanan poli menggunakan queue 
 Fungsi:
- Ambil antrian layanan ( maksimal 20/hari)
- Lihat antrian berjalan 
- Data struktur: Queue dengan array atau linked list
*/

#ifndef ANTRIAN_H
#define ANTRIAN_H

#include "../header/pasien.h"

#define MAKS_ANTRIAN 20

typedef struct {
    int nomor;
} Antrian;

typedef struct {
    Antrian queue[MAKS_ANTRIAN];
    int depan, belakang;
} Queue;

// Fungsi dasar
void initQueue(Queue *q);
int isFull(Queue *q);
int isEmpty(Queue *q);
void enqueue(Queue *q);
void dequeue(Queue *q);
int lihatDepan(Queue *q);
void tampilAntrian(Queue *q);

// Fungsi spesifik sesuai tugas kamu
void ambilAntrianLayanan(Queue *q);
void lihatAntrianLayanan(Queue *q);

#endif
