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

    Pembayaran *headPembayaran = NULL;

    initQueue(&antrianLayanan);
    initPoli(daftarPoli);

    do {
        printf("\n======================================\n");
        printf("SISTEM ADMINISTRASI PUSKESMAS\n");
        printf("1. IGD ");
        printf("2. Ambil Antrian Layanan\n");
        printf("3. Lihat Antrian Layanan\n");
        printf("4. Tambah Data Pasien Baru\n");
        printf("5. Cari Pasien Berdasarkan NIK\n");
        printf("6. Antrian Poli\n");
        printf("7. Pembayaran\n");
        printf("8. Cetak Rekam Medis\n");
        printf("9. Keluar\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);



        switch(pilihan) {
            case 1:
                // Pasien gawat darurat akan di masukkan ke IGD 
            case 2:
                // Panggil fungsi ambilAntrianLayanan(&antrianLayanan);
                break;
            case 3:
                // lihatAntrianLayanan(&antrianLayanan);
                break;
            case 4:
                // Tambah data pasien baru ke BST rootPasien
                break;
            case 5:
                // Cari pasien berdasarkan NIK
                break;
            case 6:
                // Proses antrian poli
                 menuAntrianPoli(daftarPoli, rootPasien, &headPembayaran);
                break;

            case 7:
                // Proses pembayaran
                break;
            case 8:
                // Cetak rekam medis dari BST rootPasien
                break;
            case 9:
                printf("Terima kasih telah menggunakan sistem.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while(pilihan != 8);

    return 0;
}
