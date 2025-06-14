#ifndef INPUTOUTPUT_C
#define INPUTOUTPUT_C

#include "../header.h"

// ===== IMPLEMENTASI FUNGSI INPUT/OUTPUT =====
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inputDataPasien(Pasien* pasien) {
    printf("\n=== INPUT DATA PASIEN BARU ===\n");
    
    printf("NIK (16 digit): ");
    fgets(pasien->nik, sizeof(pasien->nik), stdin);
    pasien->nik[strcspn(pasien->nik, "\n")] = 0;
    
    printf("Nama: ");
    fgets(pasien->nama, sizeof(pasien->nama), stdin);
    pasien->nama[strcspn(pasien->nama, "\n")] = 0;
    
    printf("Usia: ");
    while (scanf("%d", &pasien->usia) != 1) {
        printf("Input tidak valid! Masukkan angka: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    
    printf("Jenis Kelamin (L/P): ");
    fgets(pasien->jenisKelamin, sizeof(pasien->jenisKelamin), stdin);
    pasien->jenisKelamin[strcspn(pasien->jenisKelamin, "\n")] = 0;
    clearInputBuffer();
    
    printf("Alamat: ");
    fgets(pasien->alamat, sizeof(pasien->alamat), stdin);
    pasien->alamat[strcspn(pasien->alamat, "\n")] = 0;
    
    printf("Telepon: ");
    fgets(pasien->telepon, sizeof(pasien->telepon), stdin);
    pasien->telepon[strcspn(pasien->telepon, "\n")] = 0;
    
    printf("Status BPJS (AKTIF/NONAKTIF): ");
    fgets(pasien->statusBpjs, sizeof(pasien->statusBpjs), stdin);
    pasien->statusBpjs[strcspn(pasien->statusBpjs, "\n")] = 0;
    
    // Initialize default values
    pasien->riwayat = NULL;
    pasien->totalKunjungan = 0;
}

void inputDataKunjungan(char* tanggal, char* keluhan, char* diagnosa, char* resep, char* dokter, float* biaya) {
    printf("\n=== INPUT DATA KUNJUNGAN ===\n");
    
    printf("Tanggal kunjungan (YYYY-MM-DD): ");
    fgets(tanggal, 11, stdin);
    tanggal[strcspn(tanggal, "\n")] = 0;
    clearInputBuffer();
    
    printf("Keluhan: ");
    fgets(keluhan, 100, stdin);
    keluhan[strcspn(keluhan, "\n")] = 0;
    
    printf("Diagnosa: ");
    fgets(diagnosa, 100, stdin);
    diagnosa[strcspn(diagnosa, "\n")] = 0;
    
    printf("Resep: ");
    fgets(resep, 200, stdin);
    resep[strcspn(resep, "\n")] = 0;
    
    printf("Dokter: ");
    fgets(dokter, 50, stdin);
    dokter[strcspn(dokter, "\n")] = 0;
    
    printf("Biaya: ");
    while (scanf("%f", biaya) != 1) {
        printf("Input tidak valid! Masukkan angka: ");
        clearInputBuffer();
    }
    clearInputBuffer();
}

char* inputNikPasien(void) {
    static char nik[17];
    printf("Masukkan NIK pasien: ");
    fgets(nik, sizeof(nik), stdin);
    nik[strcspn(nik, "\n")] = 0;
    return nik;
}

int tampilkanMenu(void) {
    int pilihan;
    
    printf("\n=== SISTEM MANAJEMEN PASIEN ===\n");
    printf("1. Tambah Pasien Baru\n");
    printf("2. Cari Pasien\n");
    printf("3. Tambah Kunjungan\n");
    printf("4. Cetak Rekam Medis\n");
    printf("5. Lihat Semua Pasien\n");
    printf("6. Simpan Data\n");
    printf("0. Keluar\n");
    printf("Pilihan: ");
    
    while (scanf("%d", &pilihan) != 1) {
        printf("Input tidak valid! Masukkan angka: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    
    return pilihan;
}

void tampilkanPesanSukses(char* pesan) {
    printf("\n=== SUKSES ===\n");
    printf("%s\n", pesan);
}

void tampilkanPesanError(char* pesan) {
    printf("\n=== ERROR ===\n");
    printf("%s\n", pesan);
}

void tungguEnter(void) {
    printf("\nTekan Enter untuk melanjutkan...");
    getchar();
}

#endif