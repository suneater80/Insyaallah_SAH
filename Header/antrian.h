/*modul untuk antrian dan layanan poli menggunakan queue 
 Fungsi:
- Ambil antrian layanan ( maksimal 20/hari)
- Lihat antrian berjalan 
- Data struktur: Queue dengan array atau linked list
*/

#ifndef ANTRIAN_H
#define ANTRIAN_H
#define MAKS_ANTRIAN 20


typedef struct {
    int nomor;
    char nik[20];
} Antrian;

typedef struct {
    Antrian queue[MAKS_ANTRIAN];
    int depan, belakang;
} Queue;

void initQueue(Queue *q);
int isFull(Queue q);
int isEmpty(Queue q);
void enqueue(Queue *q, Antrian data);
Antrian dequeue(Queue *q, Pasien *p);
Antrian lihatDepan(Queue q);
void tampilAntrian(Queue q);

#endif


