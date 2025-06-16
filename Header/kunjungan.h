
#ifndef KUNJUNGAN_H
#define KUNJUNGAN_H

#include <stdio.h>

// Forward declaration untuk struct Pasien, ilmu mahal
typedef struct Pasien Pasien;

// Struktur data untuk kunjungan (linked list)
typedef struct Kunjungan {
    int idKunjungan;
    char tanggal[11];
    char keluhan[100];
    char diagnosa[100];
    char resep[200];
    char dokter[50];
    float biaya;
    struct Kunjungan *next;
} Kunjungan;

// Global counter untuk ID kunjungan
extern int globalKunjunganId;

// ===== DEKLARASI FUNGSI LINKED LIST KUNJUNGAN =====
Kunjungan* createKunjungan(char* tanggal, char* keluhan, char* diagnosa, char* resep, char* dokter, float biaya);

void tambahKunjungan(Pasien* pasien, char* tanggal, char* keluhan, char* diagnosa, char* resep, char* dokter, float biaya);
void cetakRiwayatKunjungan(Kunjungan* head);
void freeRiwayatKunjungan(Kunjungan* head);


#endif
