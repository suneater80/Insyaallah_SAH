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
        tampilkanHeader("SISTEM MANAJEMEN KLINIK");
        printf("=== UNTUK PASIEN ===\n");
        printf("1. Ambil Antrian Layanan\n");
        printf("2. Lihat Status Antrian Masuk\n");
        printf("3. Lihat Status Antrian Poli\n\n");
        
        printf("=== UNTUK PETUGAS ===\n");
        printf("4. Loket Antrian\n");
        printf("5. Dokter\n");
        printf("6. Pembayaran\n\n");
        
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
                // 
                
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

