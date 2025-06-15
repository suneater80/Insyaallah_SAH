#include "header.h"

// Deklarasi fungsi untuk menu agar main() lebih rapi
void tampilkanMenuUtama();
void menuAdministrasiPasien(NodePasien** root);
void menuManajemenPoli(Poli poli[]);

int main() {
    // 1. Inisialisasi semua struktur data
    NodePasien* rootPasien = NULL;
    QueueLayanan antrianLayanan;
    Poli daftarPoliKlinik[MAX_POLI];

    initQueueLayanan(&antrianLayanan);
    initPoli(daftarPoliKlinik);

    // 2. Muat data pasien dari file saat program dimulai
    char filename[] = "dataPasien.txt";
    rootPasien = loadPasienFromFile(filename);
    printf("Memulai Sistem Administrasi Rumah Sakit...\n");
    sleep(2);

    int pilihan;
    do {
        clearScreen();
        tampilkanMenuUtama();
        printf("Pilihan Anda: ");
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid. Masukkan angka.\n");
            clearInputBuffer(); // Gunakan fungsi dari InputOutput.c
            pilihan = -1; // Set ke nilai invalid untuk lanjut loop
            pause();
            continue;
        }
        clearInputBuffer(); // Penting untuk membersihkan buffer setelah scanf

        switch (pilihan) {
            case 1:
                // Menu untuk pasien mengambil antrian layanan
                menuAntrianLayanan(&antrianLayanan);
                break;
            case 2:
                // Menu untuk petugas loket memproses antrian
                menuLoketAntrian(&antrianLayanan);
                break;
            case 3:
                // Menu untuk manajemen poli (daftar & proses)
                menuManajemenPoli(daftarPoliKlinik);
                break;
            case 4:
                // Menu untuk administrasi data pasien (BST)
                menuAdministrasiPasien(&rootPasien);
                break;
            case 0:
                // Keluar dari program
                printf("Menyimpan semua data sebelum keluar...\n");
                saveAllPasienToFile(rootPasien, filename);
                break;
            default:
                printf("Pilihan tidak valid!\n");
                pause();
        }
    } while (pilihan != 0);

    // 5. Membersihkan memori sebelum program benar-benar berakhir
    printf("Membersihkan memori dan keluar dari program. Sampai jumpa!\n");
    freeBstPasien(rootPasien);

    return 0;
}

/**
 * @brief Menampilkan menu utama program.
 */
void tampilkanMenuUtama() {
    tampilkanHeader("SISTEM MANAJEMEN KLINIK");
    printf("1. Ambil Antrian Layanan (Untuk Pasien)\n");
    printf("2. Loket Antrian (Untuk Petugas)\n");
    printf("3. Manajemen Poli\n");
    printf("4. Administrasi Data Pasien\n");
    printf("0. Simpan & Keluar\n");
    printf("===========================\n");
}

/**
 * @brief Mengelola sub-menu untuk administrasi data pasien.
 * @param root Pointer ke root BST pasien, bisa diubah jika ada balancing.
 */
void menuAdministrasiPasien(NodePasien** root) {
    int pilihan;
    do {
        clearScreen();
        tampilkanHeader("ADMINISTRASI DATA PASIEN");
        printf("1. Tambah Pasien Baru\n");
        printf("2. Cari Pasien (NIK)\n");
        printf("3. Tambah Riwayat Kunjungan\n");
        printf("4. Lihat Semua Data Pasien (In-order)\n");
        printf("5. Seimbangkan Pohon Data Pasien (Balance BST)\n");
        printf("0. Kembali ke Menu Utama\n");
        printf("===========================\n");
        printf("Pilihan Anda: ");

        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid.\n");
            clearInputBuffer();
            pilihan = -1;
            pause();
            continue;
        }
        clearInputBuffer();

        switch (pilihan) {
            case 1: {
                Pasien pasienBaru;
                inputDataPasien(&pasienBaru);
                *root = insertPasien(*root, pasienBaru);
                tampilkanPesanSukses("Pasien baru berhasil ditambahkan!");
                pause();
                break;
            }
            case 2: {
                char* nik = inputNikPasien();
                NodePasien* hasil = searchPasien(*root, nik);
                if (hasil != NULL) {
                    cetakDataPasien(hasil->data);
                } else {
                    tampilkanPesanError("Pasien dengan NIK tersebut tidak ditemukan.");
                }
                pause();
                break;
            }
            case 3: {
                char* nik = inputNikPasien();
                NodePasien* nodePasien = searchPasien(*root, nik);
                if (nodePasien != NULL) {
                    char tanggal[11], keluhan[100], diagnosa[100], resep[200], dokter[50];
                    float biaya;
                    inputDataKunjungan(tanggal, keluhan, diagnosa, resep, dokter, &biaya);
                    tambahKunjungan(&(nodePasien->data), tanggal, keluhan, diagnosa, resep, dokter, biaya);
                    tampilkanPesanSukses("Riwayat kunjungan berhasil ditambahkan.");
                } else {
                    tampilkanPesanError("Pasien dengan NIK tersebut tidak ditemukan.");
                }
                pause();
                break;
            }
            case 4:
                clearScreen();
                tampilkanHeader("SEMUA DATA PASIEN");
                if (*root == NULL) {
                    printf("Belum ada data pasien yang tersimpan.\n");
                } else {
                    cetakSemuaPasien(*root);
                }
                pause();
                break;
            case 5:
                *root = balanceBST(*root);
                tampilkanPesanSukses("Pohon data pasien (BST) berhasil diseimbangkan.");
                pause();
                break;
            case 0:
                break;
            default:
                printf("Pilihan tidak valid!\n");
                pause();
        }
    } while (pilihan != 0);
}

/**
 * @brief Mengelola sub-menu untuk pendaftaran dan proses di poli.
 * @param poli Array dari struktur Poli.
 */
void menuManajemenPoli(Poli poli[]) {
    int pilihan;
    do {
        clearScreen();
        tampilkanHeader("MANAJEMEN POLI");
        printf("1. Daftar ke Poli\n");
        printf("2. Proses Antrian Poli (Untuk Dokter/Perawat)\n");
        printf("3. Lihat Status Semua Antrian Poli\n");
        printf("0. Kembali ke Menu Utama\n");
        printf("===========================\n");
        printf("Pilihan Anda: ");

        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid.\n");
            clearInputBuffer();
            pilihan = -1;
            pause();
            continue;
        }
        clearInputBuffer();
        
        int pilihanPoli;
        switch (pilihan) {
            case 1:
            case 2:
                printf("\nPilih Poli:\n");
                for (int i = 0; i < MAX_POLI; i++) {
                    printf("%d. %s\n", i + 1, poli[i].nama);
                }
                printf("Pilihan Poli: ");
                scanf("%d", &pilihanPoli);
                clearInputBuffer();

                if (pilihanPoli > 0 && pilihanPoli <= MAX_POLI) {
                    if (pilihan == 1) {
                        daftarPoli(&poli[pilihanPoli - 1]);
                    } else {
                        prosesAntrianPoli(&poli[pilihanPoli - 1]);
                    }
                } else {
                    printf("Pilihan Poli tidak valid.\n");
                }
                pause();
                break;
            case 3:
                lihatStatusAntrian(poli);
                break;
            case 0:
                break;
            default:
                printf("Pilihan tidak valid!\n");
                pause();
        }
    } while (pilihan != 0);
}