/* Manajemen poli & proses antrian masing-masing poli 
Fungsi:
- Pilih poli (umum/gigi/THT)
- Masuk dan proses antrian poli (7 antrian/poli)
- Pindah ke dokter
Data struktur: Queue per poli
*/

#ifndef POLI_H
#define POLI_H

#include "../header.h"

#define MAX_POLI 3

typedef struct {
    char kode;
    char nama[50];
    Queue antrian; // gunakan Queue
} Poli;

void initPoli(Poli poli[]);
void menuAntrianPoli(Poli daftarPoli[], Pasien *root, Pembayaran **headPembayaran);
void prosesAntrianPoli(Poli *poli, Pasien *root, Pembayaran **headPembayaran);

#endif


