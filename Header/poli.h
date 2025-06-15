/* Manajemen poli & proses antrian masing-masing poli 
Fungsi:
- Pilih poli (umum/gigi/THT)
- Masuk dan proses antrian poli (7 antrian/poli)
- Pindah ke dokter
Data struktur: Queue per poli
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 

#include "queuePoli.h"

#ifndef POLI_H
#define POLI_H


#define MAX_POLI 3

typedef struct {
    char nama[20];
    Queue antrian;
    int nomorTerakhir;
} Poli;

void initPoli(Poli poli[]);
void daftarPoli(Poli *poli);
void prosesAntrianPoli(Poli *poli);
void lihatStatusAntrian(Poli poli[]);
void tampilkanHeader(const char *judul);
void pause();

#endif


