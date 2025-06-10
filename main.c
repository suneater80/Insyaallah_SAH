/*Menu CLI & logika alur program
- Deklarasi global data antrian &BST pasien
- Fungsi menuUtama() --> switch case 1-8 
- Loop untuk input pilihan menu
- panggil fungsi dari file .c sesuai pilihan 
- CLI tampilan 
*/

// Template main.c
#include <stdlib.h>
#include "pasien.h"
#include "antrian.h"
#include "poli.h"
#include "kunjungan.h"
#include "rekammedis.h"
#include "pembayaran.h"

int main() {
    int pilihan;
    Pasien *rootPasien = NULL;
    Queue antrianLayanan;
    Poli daftarPoli[MAX_POLI];

    initQueue(&antrianLayanan);
    initPoli(daftarPoli);

    do {
        printf("\n======================================\n");
        printf("SISTEM ADMINISTRASI KLINIK\n");
        printf("1. Ambil Antrian Layanan\n");
        printf("2. Lihat Antrian Layanan\n");
        printf("3. Tambah Data Pasien Baru\n");
        printf("4. Cari Pasien Berdasarkan NIK\n");
        printf("5. Antrian Poli\n");
        printf("6. Pembayaran\n");
        printf("7. Cetak Rekam Medis\n");
        printf("8. Keluar\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1:
                // Panggil fungsi ambilAntrianLayanan(&antrianLayanan);
                break;
            case 2:
                // lihatAntrianLayanan(&antrianLayanan);
                break;
            case 3:
                // Tambah data pasien baru ke BST rootPasien
                break;
            case 4:
                // Cari pasien berdasarkan NIK
                break;
            case 5:
                // Proses antrian poli
                break;
            case 6:
                // Proses pembayaran
                break;
            case 7:
                // Cetak rekam medis dari BST rootPasien
                break;
            case 8:
                printf("Terima kasih telah menggunakan sistem.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while(pilihan != 8);

    return 0;
}
