/* Manajemen poli & proses antrian masing-masing poli 
Fungsi:
- Pilih poli (umum/gigi/THT)
- Masuk dan proses antrian poli (7 antrian/poli)
- Pindah ke dokter
Data struktur: Queue per poli
*/

#ifndef POLI_H
#define POLI_H

#include <stdio.h>  // Untuk fungsi input/output
#include <stdlib.h> // Untuk fungsi standar
#include <string.h> // Untuk fungsi manipulasi string
#include <time.h> // Untuk fungsi waktu (opsional jika dipakai)
#include <unistd.h> // Untuk fungsi sleep() di UNIX/Linux (gunakan Sleep() di Windows jika perlu)

#include "queue.h"
#define MAX_POLI 3 // Jumlah maksimal poli (Umum, Gigi, THT)

// Struktur data untuk menyimpan informasi sebuah poli
typedef struct {
    char nama[20]; // Nama poli, contoh: "Poli Umum"
    QueuePoli antrian; // Queue untuk menyimpan nomor antrian pasien di poli ini
    int nomorTerakhir; // Nomor antrian terakhir yang didaftarkan
} Poli;

// ====== PROTOTIPE FUNGSI ======
void tampilkanHeader(const char *judul); // Inisialisasi daftar poli dan antrian
void initPoli(Poli poli[]); //Tambah pasien ke antrian poli
void daftarPoli(Poli *poli); // Proses pasien dalam antrian poli
void prosesAntrianPoli(Poli *poli); // Tampilkan status antrian semua poli
void lihatStatusAntrian(Poli poli[]); // Tampilkan header dengan judul tertentu
void pause();  // Pause program, tunggu input ENTER

#endif