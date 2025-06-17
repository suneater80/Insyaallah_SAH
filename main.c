#include "header.h"


int main() {
    // Inisialisasi semua struktur data
    NodePasien* rootPasien = NULL;
    QueueLayanan antrianLayanan;
    Poli daftarPoliKlinik[MAX_POLI];

    Pembayaran *headPembayaran = NULL;

    initQueueLayanan(&antrianLayanan);
    initPoli(daftarPoliKlinik);

    // Muat data pasien dari file saat program dimulai
    char filename[] = "dataPasien.txt";
    rootPasien = loadPasienFromFile(filename);
    printf("Memulai Sistem Administrasi Puskesmas...\n");
    sleep(2);

    int pilihan;
    do {
        clearScreen();
        tampilkanHeader("SISTEM ADMINISTRASI PUSKESMAS");
        printf("1. Layanan IGD \n");
        printf("2. Pengambilan Antrian Calon Pasien \n");
        printf("3. Lihat Status Antrian Calon Pasien\n");
        printf("4. Proses Antrian Calon Pasien\n");
        printf("5. Layanan Poli\n");
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
                // ==== LAYANAN IGD ====
                layananIGD(daftarPoliKlinik);
                break;

            case 2:
                //
                menuAntrianLayanan(&antrianLayanan);
                break;

            case 3:
                //
                tampilkanStatusAntrian(&antrianLayanan);
                
                break;
                
            case 4:
                prosesLoketAntrian(&antrianLayanan);
                break;

            case 5:
            // ==== LAYANAN POLI ====
            {
                int pilihanPoli; // Variabel baru untuk input dalam submenu poli

                do {
                    clearScreen();
                    tampilkanHeader("MENU UTAMA POLI");
                    printf("1. Daftar Antrian Poli\n");
                    printf("2. Proses Antrian Poli\n");
                    printf("3. Lihat Status Antrian Poli\n");
                    printf("0. Kembali ke Menu Utama\n");
                    printf("Pilihan: ");
                    scanf("%d", &pilihanPoli);

                    switch (pilihanPoli) {
                        case 1:
                            clearScreen();
                            tampilkanHeader("DAFTAR ANTRIAN POLI");
                            printf("1. Poli Umum\n");
                            printf("2. Poli Gigi\n");
                            printf("3. Poli THT\n");
                            printf("Pilihan: ");    
                            scanf("%d", &pilihanPoli);
                            if (pilihanPoli >= 1 && pilihanPoli <= 3)
                                daftarPoli(&daftarPoliKlinik[pilihanPoli - 1]);
                            else
                                printf("Pilihan tidak valid!\n");
                            pause();
                            break;

                        case 2:
                            clearScreen();
                            tampilkanHeader("PROSES ANTRIAN POLI");
                            printf("1. Poli Umum\n");
                            printf("2. Poli Gigi\n");
                            printf("3. Poli THT\n");
                            printf("Pilihan: ");
                            scanf("%d", &pilihanPoli);
                            if (pilihanPoli >= 1 && pilihanPoli <= 3)
                                prosesAntrianPoli(&daftarPoliKlinik[pilihanPoli - 1]);
                            else
                                printf("Pilihan tidak valid!\n");
                            pause();
                            break;

                        case 3:
                            lihatStatusAntrian(daftarPoliKlinik);
                            break;

                        case 0:
                            break; // Kembali ke menu utama puskesmas
                        default:
                            printf("Pilihan tidak valid!\n");
                            pause();
                    }

                } while (pilihanPoli != 0);

                break;
            }

                break;
            case 6:
                // 
                
                break;

            case 7:
                menuPembayaran(rootPasien, &headPembayaran);

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

    // Membersihkan memori
    printf("Membersihkan memori dan keluar dari program. Terima Kasih!\n");
    freeBstPasien(rootPasien);

    return 0;
}

