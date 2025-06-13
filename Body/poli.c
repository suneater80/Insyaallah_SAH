/*Implementasi fungsi proses antrian poli*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // untuk sleep()
#include "../header/poli.h"
#include "../header/kunjungan.h"
#include "../header/pembayaran.h"

// Fungsi inisialisasi daftar Poli
void initPoli(Poli poli[]) {
    char kodePoli[MAX_POLI] = {'U', 'G', 'T'};
    char *namaPoli[MAX_POLI] = {"Poli Umum", "Poli Gigi", "Poli THT"};

    for (int i = 0; i < MAX_POLI; i++) {
        poli[i].kode = kodePoli[i];
        strcpy(poli[i].nama, namaPoli[i]);
        initQueue(&poli[i].antrian);
    }
}

// Fungsi untuk menampilkan menu pemilihan Poli
void menuAntrianPoli(Poli daftarPoli[], Pasien *root, Pembayaran **headPembayaran) {
    int pilihan;
    printf("ANTRIAN POLI\n");
    printf("Silakan pilih:\n");
    printf("1.Poli Umum\n");
    printf("2.Poli Gigi\n");
    printf("3.Poli THT\n");
    printf("Pilihan: ");
    scanf("%d", &pilihan);
    getchar(); // buang newline

    if (pilihan < 1 || pilihan > MAX_POLI) {
        printf("Pilihan tidak valid.\n");
        return;
    }

    prosesAntrianPoli(&daftarPoli[pilihan - 1], root, headPembayaran);
}

// Fungsi proses antrian Poli
void prosesAntrianPoli(Poli *poli, Pasien *root, Pembayaran **headPembayaran)
 {
    if (isEmptyQueue(&poli->antrian)) {
        printf("❗ Tidak ada pasien dalam antrian %s.\n", poli->nama);
        return;
    }

    Pasien dataPasien;
    dequeue(&poli->antrian);
    printf("⏳ Memproses antrian pertama di %s...\n", poli->nama);
    printf("🩺 %s telah dilakukan tindak oleh dokter.\n", dataPasien.nama);

    printf("(Menunggu 5 detik...)\n");
    sleep(5);

    Pasien *pasienBST = cariPasien(root, dataPasien.NIK);
    if (pasienBST != NULL) {
        tambahKunjungan(pasienBST); // minta input kunjungan pasien
    } else {
        printf("❗ Data pasien tidak ditemukan di database!\n");
        return;
    }

    Pembayaran pembayaran;
    strcpy(pembayaran.NIK, dataPasien.NIK);
    strcpy(pembayaran.nama, dataPasien.nama);
    strcpy(pembayaran.poli, poli->nama);
    strcpy(pembayaran.status_BPJS, dataPasien.status_BPJS);
    
    // Simulasi biaya tergantung poli
    if (strcmp(pembayaran.status_BPJS, "Ya") == 0) {
        pembayaran.biaya = 0;
    } else {
        if (poli->kode == 'U') pembayaran.biaya = 30000;
        else if (poli->kode == 'G') pembayaran.biaya = 50000;
        else if (poli->kode == 'T') pembayaran.biaya = 45000;
    }

    tambahAntrianPembayaran(headPembayaran, pembayaran);

    printf("➡ Pasien masuk ke daftar pembayaran.\n");
    printf("Tekan Enter untuk lanjut...");
    getchar();
}

