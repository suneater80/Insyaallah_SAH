/* Struktur data & fungsi untuk data pasien (termasuk rekam medis & BST)
*/ 
#ifndef PASIEN_H
#define PASIEN_H
#include "../header.h"


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


// Global counter untuk ID kunjungan
extern int globalKunjunganId;

// ===== DEKLARASI FUNGSI LINKED LIST KUNJUNGAN =====
Kunjungan* createKunjungan(char* tanggal, char* keluhan, char* diagnosa, char* resep, char* dokter, float biaya);

void tambahKunjungan(Pasien* pasien, char* tanggal, char* keluhan, char* diagnosa, char* resep, char* dokter, float biaya);
void cetakRiwayatKunjungan(Kunjungan* head);
void freeRiwayatKunjungan(Kunjungan* head);

// ===== DEKLARASI FUNGSI BST PASIEN =====
NodePasien* createNodePasien(Pasien pasien);
NodePasien* insertPasien(NodePasien* root, Pasien pasien);
NodePasien* searchPasien(NodePasien* root, char* nik);
void cetakDataPasien(Pasien pasien);
void cetakSemuaPasien(NodePasien* root);
void freeBstPasien(NodePasien* root);

// ===== DEKLARASI FUNGSI FILE OPERATIONS =====
void savePasienToFile(NodePasien* root, FILE* file);
void saveAllPasienToFile(NodePasien* root, char* filename);
NodePasien* loadPasienFromFile(char* filename);

// ===== DEKLARASI FUNGSI INPUT/OUTPUT =====
void inputDataPasien(Pasien* pasien);
void inputDataKunjungan(char* tanggal, char* keluhan, char* diagnosa, char* resep, char* dokter, float* biaya);
void clearInputBuffer(void);

#endif

