/* Struktur data & fungsi untuk data pasien (termasuk rekam medis & BST)
*/ 
#ifndef PASIEN_H
#define PASIEN_H
#include <stdio.h>


// Forward declaration untuk struct Kunjungan
typedef struct Kunjungan Kunjungan;


// Struktur data untuk pasien
typedef struct Pasien {
    char nik[17];
    char nama[50];
    int usia;
    char jenisKelamin[2];
    char alamat[100];
    char telepon[20];
    char statusBpjs[10];
    Kunjungan *riwayat;
    int totalKunjungan;
} Pasien;

// Node BST untuk pasien
typedef struct NodePasien {
    Pasien data;
    struct NodePasien *left;
    struct NodePasien *right;
} NodePasien;


// ===== DEKLARASI FUNGSI BST PASIEN =====
NodePasien* createNodePasien(Pasien pasien);
NodePasien* insertPasien(NodePasien* root, Pasien pasien);
NodePasien* searchPasien(NodePasien* root, char* nik);
void cetakDataPasien(Pasien pasien);
void cetakSemuaPasien(NodePasien* root);
void freeBstPasien(NodePasien* root);

#endif

