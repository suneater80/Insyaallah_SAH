/* Struktur data & fungsi untuk data pasien (termasuk rekam medis & BST)
*/ 

#ifndef PASIEN_H
#define PASIEN_H

#define MAX_NAMA 50
#define MAX_ALAMAT 100
#define MAX_TELPON 20

typedef struct Kunjungan {
    char tanggal[11];
    char keluhan[100];
    char diagnosa[100];
    char resep[100];
    struct Kunjungan *next;
} Kunjungan;

typedef struct Pasien {
    char NIK[20];
    char nama[MAX_NAMA];
    int usia;
    char jenis_kelamin;
    char alamat[MAX_ALAMAT];
    char telepon[MAX_TELPON];
    char status_BPJS[10];
    Kunjungan *riwayat;

    struct Pasien *left, *right;  // Untuk BST
} Pasien;

Pasien* tambahPasien(Pasien *root, Pasien baru);
Pasien* cariPasien(Pasien *root, char NIK[]);
void tampilkanDataPasien(Pasien *pasien);
void preorder(Pasien *root);

#endif

