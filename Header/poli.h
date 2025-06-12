/* Manajemen poli & proses antrian masing-masing poli 
Fungsi:
- Pilih poli (umum/gigi/THT)
- Masuk dan proses antrian poli (7 antrian/poli)
- Pindah ke dokter
Data struktur: Queue per poli
*/

#ifndef POLI_H
#define POLI_H

#include "antrian.h"
#include "pasien.h"
#include "pembayaran.h"

#define MAX_POLI 3
#define MAX_ANTRI_POLI 7

typedef struct {
    char kode; // kode poli : 'U' untuk Umum, 'G' untuk gigi, 'T' untuk THT 
    char nama[20]; // Nama poli ("Poli umum", "Poli Gigi", "Poli THT")
    Queue antrian; //Queue untuk antrian Poli 
} Poli;

void initPoli(Poli poli[]);
void menuAntrianPoli(Poli daftarPoli[], Pasien *root, Pembayaran **headPembayaran);
void prosesAntrianPoli(Poli *poli);

#endif

