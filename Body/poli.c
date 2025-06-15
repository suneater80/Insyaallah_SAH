/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Untuk sleep() 
*/
#include "../header.h"

void initPoli(Poli poli[]) {
    strcpy(poli[0].nama, "Poli Umum");
    strcpy(poli[1].nama, "Poli Gigi");
    strcpy(poli[2].nama, "Poli THT");

    for (int i = 0; i < MAX_POLI; i++) {
        initQueue(&poli[i].antrian);
        poli[i].nomorTerakhir = 0;
    }
}

void daftarPoli(Poli *poli) {
    if (isFull(&poli->antrian)) {
        printf("Maaf, antrian %s sudah penuh!\n", poli->nama);
        return;
    }
    poli->nomorTerakhir++;
    enqueue(&poli->antrian, poli->nomorTerakhir);
    printf("Pendaftaran berhasil!\nNomor antrian Anda untuk %s: %d\n", poli->nama, poli->nomorTerakhir);
}

void prosesAntrianPoli(Poli *poli) {
    if (isEmpty(&poli->antrian)) {
        printf("Tidak ada pasien dalam antrian %s.\n", poli->nama);
        return;
    }

    int nomor = peek(&poli->antrian);
    printf("Pasien nomor %d sedang diperiksa di %s...\n", nomor, poli->nama);

    // Countdown contoh 5 detik (bisa ubah ke 60 jika mau)
    for (int i = 5; i >= 0; i--) {
        printf("\rSisa waktu: %2d detik ", i);
        fflush(stdout);
        sleep(1);
    }

    printf("\nPasien nomor %d selesai diperiksa.\n\n", dequeue(&poli->antrian));

    if (isEmpty(&poli->antrian)) {
        printf("Semua pasien di %s telah diperiksa.\n", poli->nama);
    } else {
        printf("Masih ada pasien dalam antrian %s.\n", poli->nama);
    }
}


void lihatStatusAntrian(Poli poli[]) {
    tampilkanHeader("STATUS ANTRIAN POLI");
    for (int i = 0; i < MAX_POLI; i++) {
        printf("%d. %s\n", i + 1, poli[i].nama);
        printf("   Total Antrian    : %d\n", getCount(&poli[i].antrian));
        printf("   Nomor Terakhir   : %d\n", poli[i].nomorTerakhir);
        if (!isEmpty(&poli[i].antrian))
            printf("   Sedang Dilayani  : %d\n", peek(&poli[i].antrian));
        printf("\n");
    }
    pause();
}

void tampilkanHeader(const char *judul) {
    printf("\n===========================\n");
    printf(" %s\n", judul);
    printf("===========================\n");
}

void pause() {
    printf("Tekan ENTER untuk melanjutkan...");
    getchar();
    getchar();
}
