#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

// Untuk Binary tree dan linked list kunjungan
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



// Queue
typedef struct QueueNode {
    char namaPasien; // Menyimpan nama pasien yang antri, nanti akan dihapus jika telah antri
    int nomorAntrian; 
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
    int count; // Jumlah pasien dalam antrian
    int lastNomorAntrian; // Untuk generate nomor antrian berikutnya
} Queue;


// Undo jika jadi dibuat
typedef enum {
    OPERASI_TAMBAH_PASIEN,
    OPERASI_UPDATE_REKAM_MEDIS
    // Tambahkan jenis operasi lain jika diperlukan
} JenisOperasi;

typedef struct UndoRedoAction {
    JenisOperasi tipeOperasi;
    void *dataSebelum; // Data sebelum operasi , undo
    void *dataSesudah; // Data sesudah operasi , redo
} UndoRedoAction;

typedef struct StackNode {
    UndoRedoAction aksi;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
} Stack;


#endif