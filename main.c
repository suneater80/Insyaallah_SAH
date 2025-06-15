/*Menu CLI & logika alur program
- Deklarasi global data antrian &BST pasien
- Fungsi menuUtama() --> switch case 1-8 
- Loop untuk input pilihan menu
- panggil fungsi dari file .c sesuai pilihan 
- CLI tampilan 
*/

// Template main.c
#include "header.h"

int main() {
    int pilihan;
    Queue antrianLayanan;

    initQueue(&antrianLayanan);

    do {
        printf("\n======================================\n");
        printf("SISTEM ADMINISTRASI PUSKESMAS\n");
        printf("1. IGD\n");
        printf("2. Ambil Antrian Layanan\n");
        printf("3. Lihat Antrian Layanan\n");
        printf("4. Tambah Data Pasien Baru\n");
        printf("5. Cari Data Pasien\n");
        printf("6. Poli\n");
        printf("7. Pembayaran\n");
        printf("8. Cetak Rekam Medis\n");
        printf("9. Keluar\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);



        switch(pilihan) {
            case 1:
                // Pasien gawat darurat akan di masukkan ke IGD 
            case 2:
                menuAntrianLayanan(&antrianLayanan);
                break;
            case 3:
                tampilkanStatusAntrian(&antrianLayanan);
                break;
            case 4:
                // Tambah data pasien baru ke BST rootPasien
                break;
            case 5:
                // Cari pasien berdasarkan NIK
                break;
            case 6:
                // Proses antrian poli
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
