#ifndef POLI_H
#define POLI_H

#include <stdio.h>  // Untuk fungsi input/output
#include <stdlib.h> // Untuk fungsi standar
#include <string.h> // Untuk fungsi manipulasi string
#include <time.h> // Untuk fungsi waktu (opsional jika dipakai)
#include <unistd.h> // Untuk fungsi sleep() di UNIX/Linux (gunakan Sleep() di Windows jika perlu)

#include "queue.h"
#include "antrian.h"
#include "pasien.h"
#define MAX_POLI 3 // Jumlah maksimal poli (Umum, Gigi, THT)

// Struktur data untuk menyimpan informasi sebuah poli
typedef struct {
    char nama[20];
   QueuePoli antrianIGD;      // <-- Tambahkan queue untuk prioritas IGD
    QueuePoli antrian;         // Queue antrian biasa
    int nomorTerakhir;     // Untuk antrian biasa
    int nomorTerakhirIGD;  // <-- Tambahkan nomor antrian untuk IGD
} Poli;

// ====== DEKLARASI FUNGSI ======
void tampilkanHeader(const char *judul); // Inisialisasi daftar poli dan antrian
void initPoli(Poli poli[]); //Tambah pasien ke antrian poli
void daftarPoli(Poli *poli); // Proses pasien dalam antrian poli
void prosesAntrianPoli(Poli *poli, NodePasien** rootPasien); // Tampilkan status antrian semua poli
void lihatStatusAntrian(Poli poli[]); // Tampilkan header dengan judul tertentu
void pause();  // Pause program, tunggu input ENTER

#endif