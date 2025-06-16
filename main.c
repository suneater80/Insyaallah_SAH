#include "header.h"


int main() {
    // Inisialisasi semua struktur data
    NodePasien* rootPasien = NULL;
    QueueLayanan antrianLayanan;
    Poli daftarPoliKlinik[MAX_POLI];

    initQueueLayanan(&antrianLayanan);
    initPoli(daftarPoliKlinik);

    // Muat data pasien dari file saat program dimulai
    char filename[] = "dataPasien.txt";
    rootPasien = loadPasienFromFile(filename);
    printf("Memulai Sistem Administrasi Rumah Sakit...\n");
    sleep(2);

    int pilihan;
    do {
        clearScreen();
        tampilkanHeader("SISTEM ADMINISTRASI PUSKESMAS");
        printf("1. Layanan Pengambilan Antrian \n");
        printf("2. Lihat Status Antrian\n");
        printf("3. Layanan Poli\n");
        printf("5. Input Data Kunjungan\n");
        printf("6. Cetak Rekam Medis\n");
        printf("7. Pembayaran\n");
        printf("0. Keluar\n");
        printf("===========================\n");
        printf("Pilihan Anda: ");

        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid. Masukkan angka.\n");
            clearInputBuffer(); 
            pilihan = -1; 
            pause();
            continue;
        }
        clearInputBuffer(); // jika buffer masih ada, di loop berikutny tidak akan meminta input

        switch (pilihan) {
            case 1:
                // 
                
                break;
            case 2:
                // 
                
                break;
            case 3:
                // ===== MODUL LAYANAN POLI ======
                panggilPoli();
                
                break;
            case 4:
                // 

                break;
            case 5:
                // 

                break;
            case 6:
                // 

                break;

            case 7:
                //

                break;
                
            case 0:
                // Keluar dari program
                tampilkanHeader("TERIMA KASIH");
                printf("Terima kasih telah menggunakan sistem kami.\n");
                saveAllPasienToFile(rootPasien, filename);
                break;
            default:
                printf("Pilihan tidak valid!\n");
                pause();
        }
    } while (pilihan != 0);

    // 5. Membersihkan memori sebelum program benar-benar berakhir
    printf("Membersihkan memori dan keluar dari program. Terima Kasih!\n");
    freeBstPasien(rootPasien);

    return 0;
}

