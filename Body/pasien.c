/*Implementasi fungsi tambah pasien, cari pasien (BST), riwayat kunjungan*/

#ifndef PASIEN_H
#define PASIEN_H

typedef struct Kunjungan {
    char tanggal[11];
    char keluhan[50];
    char diagnosa[50];
    char resep[50];
    struct Kunjungan *next;
} Kunjungan;

typedef struct Pasien {
    char nik[20];
    char nama[50];
    int usia;
    char jk[10];
    char alamat[100];
    char telp[20];
    char status_bpjs[10];
    Kunjungan *riwayat;
} Pasien;

void tambahPasien(Pasien p);
void cariPasien(char *nik);

#endif
