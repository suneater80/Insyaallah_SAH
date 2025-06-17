#ifndef IGD_H
#define IGD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Fungsi sleep()
#include "poli.h"

#define MAX_IGD 1000 // Maksimal antrian IGD biasa

typedef struct {
    int nomorAntrian[MAX_IGD]; // Array untuk menyimpan nomor antrian pasien IGD biasa
    int front; // Indeks depan antrian
    int rear; // Indeks belakang antrian
    int count; // Jumlah elemen dalam antrian
    int nomorTerakhir; // Menyimpan nomor antrian terakhir
} IGDQueue;


// ===== DEKLARASI FUNGSI =====
void initIGD(IGDQueue *q);                  // Menginisialisasi queue IGD biasa
void daftarIGD(IGDQueue *q);                // Daftar IGD biasa
void prosesIGDBiasa(IGDQueue *q, Poli poli[]); // Memproses pasien IGD biasa
void prosesEmergencyIGD(Poli poli[]);      // Memproses pasien IGD emergency
void lihatStatusIGD(IGDQueue *q);          // Menampilkan status antrian IGD biasa
void layananIGD(Poli poli[]);              // Menu utama layanan IGD
void daftarPoliIGD(Poli *poli);            // Memasukkan pasien IGD ke antrian prioritas poli


#endif
