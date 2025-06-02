// Folder Struktur:

// Template main.c
#include "Header/antrian.h"
#include "Header/pasien.h"
#include "Header/dokter.h"
#include "Header/pembayaran.h"
#include "Header/poli.h"
#include "Header/rekamMedis.h"

int main() {
    int pilihan;
    do {
        tampilkanMenu();
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);
        switch (pilihan) {
            case 1:
                ambilAntrianLayanan();
                break;
            case 2:
                lihatAntrianLayanan();
                break;
            case 3:
                tambahPasienBaru();
                break;
            case 4:
                cariPasien();
                break;
            case 5:
                cetakRekamMedis();
                break;
            case 0:
                printf("Keluar...\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while(pilihan != 0);
    return 0;
}

// Header antrian.h
#ifndef ANTRIAN_H
#define ANTRIAN_H

void ambilAntrianLayanan();
void lihatAntrianLayanan();

#endif

// Header pasien.h

#ifndef PASIEN_H
#define PASIEN_H

typedef struct Kunjungan {
char tanggal[20];
char keluhan[100];
char diagnosa[100];
char resep[100];
struct Kunjungan* next;
} Kunjungan;

typedef struct Pasien {
char nik[20];
char nama[50];
int usia;
char gender[10];
char statusBPJS[10];
Kunjungan* riwayat;
} Pasien;

void tambahPasienBaru();
void simpanPasienKeFile(Pasien p);

#endif

// Header poli.h

#ifndef POLI_H
#define POLI_H

void pilihPoli(Pasien* p);
void masukAntrianPoli(Pasien* p);
void prosesAntrianPoli();

#endif

// Header rekamMedis.h

#ifndef REKAMMEDIS_H
#define REKAMMEDIS_H

void cetakRekamMedis();

#endif

// Header dokter.h

#ifndef DOKTER_H
#define DOKTER_H

void prosesPemeriksaan(Pasien* p);

#endif

// Header pembayaran.h

#ifndef PEMBAYARAN_H
#define PEMBAYARAN_H

void masukAntrianPembayaran(Pasien* p);
void cetakTagihanPasien(Pasien* p);

#endif