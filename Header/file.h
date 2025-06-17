#ifndef FILE_H
#define FILE_H

#include <stdio.h>

// Forward declarations - tidak perlu include pasien.h
typedef struct NodePasien NodePasien;
typedef struct Pasien Pasien;

// ===== DEKLARASI FUNGSI FILE OPERATIONS =====
void savePasienToFile(NodePasien* root, FILE* file);
void saveAllPasienToFile(NodePasien* root, char* filename);
NodePasien* loadPasienFromFile(char* filename);

// ===== DEKLARASI FUNGSI INPUT/OUTPUT =====
void inputDataPasien(Pasien* pasien);
void inputDataKunjungan(char* tanggal, char* keluhan, char* diagnosa, char* resep, char* dokter, float* biaya);
void clearInputBuffer(void);

// Deklarasi fungsi input/output eksternal
char* inputNikPasien(void);
int tampilkanMenu(void);
int tampilkanMenu2(void);
void tampilkanPesanSukses(char* pesan);
void tampilkanPesanError(char* pesan);
void tungguEnter(void);

#endif