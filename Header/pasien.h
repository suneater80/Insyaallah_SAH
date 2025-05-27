#ifndef PASIEN_H
#define PASIEN_H
#include "header.h"

// Binary tree dan linked list kunjungan
typedef struct Pasien {
    char nik; // NIK umumnya 16 digit + null terminator, nanti akan dialokasikan statis saja
    char nama;
    int usia; // usia paling panjang kemungkinan 3 digit, apakah bisa di efisiensikan?
    char jenisKelamin; 
    bool statusBpjs; // true jika peserta BPJS, false jika umum
    Kunjungan *riwayatKunjungan; // Pointer ke head dari linked list riwayat kunjungan
    struct Pasien *left;
    struct Pasien *right;
} Pasien;

typedef struct Kunjungan {
    char tanggalKunjungan; // Format DD-MM-YYYY
    char keluhan;
    char diagnosa; // jika sempat
    char resepObat; // sekarang input manual oleh dokter terlebih dahulu
    struct Kunjungan *next;
} Kunjungan;




#endif