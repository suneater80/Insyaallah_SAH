#include <stdio.h>
#include "header.h"

void showMenu(){
    printf("=====================================\n");
    printf("  SISTEM ADMINISTRASI RUMAH SAKIT\n");
    printf("=====================================\n");
    printf("1. Ambil Antrian Pelayanan\n");
    printf("2. Antrian Layanan\n");
    printf("3. Tambah Data Pasien Baru\n");
    printf("4. Cari Pasien (berdasarkan NIK)\n");
    printf("5. Tambah Data Kunjungan Pasien\n");
    printf("6. Cetak Rekam Medis Pasien\n");
    printf("7. Lihat Antrian Poli\n");
    printf("8. Lihat Daftar Semua Pasien\n");
    printf("9. Pembayaran\n");
    printf("10. Keluar\n");
    printf("=====================================\n");
    printf("Pilih menu [1-10]: ");
}

