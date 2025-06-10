/* Manajemen poli & proses antrian masing-masing poli 
Fungsi:
- Pilih poli (umum/gigi/THT)
- Masuk dan proses antrian poli (7 antrian/poli)
- Pindah ke dokter
Data struktur: Queue per poli
*/

#ifndef POLI_H
#define POLI_H

#define MAX_POLI 3
#define MAX_ANTRI_POLI 7

typedef struct {
    char kode; // U, G, T
    Queue antrian;
} Poli;

void initPoli(Poli poli[]);
void prosesAntrianPoli(Poli *poli);

#endif