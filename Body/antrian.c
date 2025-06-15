#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header.h"

#ifndef ANTRIAN_C
#define ANTRIAN_C

#ifdef _WIN32
#include <windows.h>
#define CLEAR() system("cls")
#else
#include <unistd.h>
#define CLEAR() system("clear")
#endif

void pause() {
    printf("\nTekan ENTER untuk kembali ke menu...");
    getchar(); getchar();
}

void menuAntrianLayanan(Queue *antrian) {
    CLEAR();
    if (isFull(antrian)) {
        printf("Antrian sudah habis untuk hari ini. Terima kasih telah berkunjung.\n");
        pause();
        return;
    }

    printf("Antrian masih tersedia dan Anda akan mengambil antrian.\n");
    printf("Silakan pilih kategori pasien:\n");
    printf("1. Umum\n");
    printf("2. BPJS\n");
    printf("Pilihan Anda: ");

    int pilihan;
    scanf("%d", &pilihan);

    Kategori kategori;
    if (pilihan == 1) {
        kategori = UMUM;
    } else if (pilihan == 2) {
        kategori = BPJS;
    } else {
        printf("Pilihan tidak valid.\n");
        pause();
        return;
    }

    if (enqueue(antrian, kategori)) {
        char awalan = (kategori == UMUM) ? 'U' : 'B';
        int nomor = antrian->data[antrian->rear].nomor;
        printf("\nAntrian berhasil diambil\n");
        printf("Nomor Antrian Anda: %c-%02d\n", awalan, nomor);
    } else {
        printf("\nGagal mengambil antrian.\n");
    }

    pause();
}

void tampilkanStatusAntrian(Queue *antrian) {
    CLEAR();
    printf("\nCEK STATUS ANTRIAN LAYANAN PASIEN\n");

    if (!isEmpty(antrian)) {
        int sedangDipanggil = antrian->data[antrian->front].nomor;
        int antrianSelanjutnya = (antrian->count > 1) ? antrian->data[(antrian->front + 1) % MAX_ANTRIAN].nomor : -1;

        printf("Sedang Dipanggil : %02d\n", sedangDipanggil);
        if (antrianSelanjutnya != -1)
            printf("Antrian Selanjutnya : %02d\n", antrianSelanjutnya);
        else
            printf("Antrian Selanjutnya : -\n");
        printf("Sisa Antrian : %d\n", antrian->count - 1);
        printf("Waktu Tunggu : %d menit\n", (antrian->count - 1) * 5);
    } else {
        printf("Tidak ada antrian saat ini.\n");
    }

    pause();
}

#endif