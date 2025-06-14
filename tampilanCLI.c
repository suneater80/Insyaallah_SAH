#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Struktur data yang sudah diberikan
typedef struct Kunjungan {
    int idKunjungan;
    char tanggal[11];
    char keluhan[100];
    char diagnosa[100];
    char resep[200];
    char dokter[50];
    float biaya;
    struct Kunjungan *next;
} Kunjungan;

typedef struct Pasien {
    char nik[17];
    char nama[50];
    int usia;
    char jenisKelamin[2];
    char alamat[100];
    char telepon[20];
    char statusBpjs[10];
    Kunjungan *riwayat;
    int totalKunjungan;
} Pasien;

typedef struct NodePasien {
    Pasien data;
    struct NodePasien *left;
    struct NodePasien *right;
} NodePasien;

// Global variables untuk antrian
int antrian_masuk_umum = 0, antrian_masuk_bpjs = 0;
int current_antrian_masuk = 0;
int antrian_poli_umum = 0, antrian_poli_gigi = 0, antrian_poli_tht = 0;
int current_poli_umum = 1, current_poli_gigi = 1, current_poli_tht = 1;

// Fungsi utilitas
void clearScreen() {
    system("cls || clear");
}

void pause() {
    printf("\nTekan Enter untuk melanjutkan...");
    getchar();
    getchar();
}

void tampilkanHeader(char* judul) {
    clearScreen();
    printf("===============================================\n");
    printf("        SISTEM ADMINISTRASI RUMAH SAKIT       \n");
    printf("===============================================\n");
    printf("           %s\n", judul);
    printf("===============================================\n\n");
}

// ============= MODUL PASIEN (AMBIL ANTRIAN) =============
void ambilAntrian() {
    int pilihan;
    tampilkanHeader("AMBIL ANTRIAN");
    
    printf("Pilih Jenis Layanan:\n");
    printf("1. Umum\n");
    printf("2. BPJS\n");
    printf("0. Kembali ke Menu Utama\n");
    printf("\nPilihan: ");
    scanf("%d", &pilihan);
    
    switch(pilihan) {
        case 1:
            antrian_masuk_umum++;
            current_antrian_masuk++;
            printf("\n=== TIKET ANTRIAN ===\n");
            printf("Nomor Antrian: UMUM-%d\n", antrian_masuk_umum);
            printf("Antrian Anda: %d\n", current_antrian_masuk);
            printf("====================\n");
            printf("Silakan menunggu panggilan loket antrian\n");
            pause();
            break;
        case 2:
            antrian_masuk_bpjs++;
            current_antrian_masuk++;
            printf("\n=== TIKET ANTRIAN ===\n");
            printf("Nomor Antrian: BPJS-%d\n", antrian_masuk_bpjs);
            printf("Antrian Anda: %d\n", current_antrian_masuk);
            printf("====================\n");
            printf("Silakan menunggu panggilan loket antrian\n");
            pause();
            break;
        case 0:
            return;
        default:
            printf("Pilihan tidak valid!\n");
            pause();
            ambilAntrian();
    }
}

void lihatAntrianMasuk() {
    tampilkanHeader("STATUS ANTRIAN MASUK");
    
    printf("Total Antrian: %d\n", current_antrian_masuk);
    printf("Antrian Sekarang: %d\n", current_antrian_masuk > 0 ? 1 : 0);
    printf("Antrian Selanjutnya: %d\n", current_antrian_masuk > 1 ? 2 : 0);
    printf("\nRincian Antrian:\n");
    printf("- UMUM: %d orang\n", antrian_masuk_umum);
    printf("- BPJS: %d orang\n", antrian_masuk_bpjs);
    
    pause();
}

// ============= MODUL LOKET ANTRIAN =============
void inputDataPasienBaru() {
    tampilkanHeader("INPUT DATA PASIEN BARU");
    
    printf("=== Data Pasien Baru ===\n");
    printf("NIK: [Input NIK]\n");
    printf("Nama: [Input Nama]\n");
    printf("Usia: [Input Usia]\n");
    printf("Jenis Kelamin (L/P): [Input Jenis Kelamin]\n");
    printf("Alamat: [Input Alamat]\n");
    printf("Telepon: [Input Telepon]\n");
    printf("Status BPJS (Ya/Tidak): [Input Status BPJS]\n");
    printf("\nData pasien berhasil disimpan!\n");
    
    pause();
}

void cariPasienLama() {
    tampilkanHeader("CARI DATA PASIEN LAMA");
    
    printf("Masukkan NIK Pasien: [Input NIK]\n");
    printf("\n=== Data Pasien Ditemukan ===\n");
    printf("NIK: 1234567890123456\n");
    printf("Nama: John Doe\n");
    printf("Usia: 30 tahun\n");
    printf("Jenis Kelamin: L\n");
    printf("Alamat: Jl. Contoh No. 123\n");
    printf("Telepon: 08123456789\n");
    printf("Status BPJS: Ya\n");
    printf("Total Kunjungan: 5\n");
    
    pause();
}

void pilihPoli() {
    int pilihan;
    tampilkanHeader("PILIH POLI");
    
    printf("Pilih Poli Tujuan:\n");
    printf("1. Poli Umum\n");
    printf("2. Poli Gigi\n");
    printf("3. Poli THT\n");
    printf("0. Kembali\n");
    printf("\nPilihan: ");
    scanf("%d", &pilihan);
    
    switch(pilihan) {
        case 1:
            antrian_poli_umum++;
            printf("\n=== TIKET ANTRIAN POLI ===\n");
            printf("Poli: UMUM\n");
            printf("Nomor Antrian: %d\n", antrian_poli_umum);
            printf("========================\n");
            printf("Silakan menuju Poli Umum dan menunggu panggilan\n");
            break;
        case 2:
            antrian_poli_gigi++;
            printf("\n=== TIKET ANTRIAN POLI ===\n");
            printf("Poli: GIGI\n");
            printf("Nomor Antrian: %d\n", antrian_poli_gigi);
            printf("========================\n");
            printf("Silakan menuju Poli Gigi dan menunggu panggilan\n");
            break;
        case 3:
            antrian_poli_tht++;
            printf("\n=== TIKET ANTRIAN POLI ===\n");
            printf("Poli: THT\n");
            printf("Nomor Antrian: %d\n", antrian_poli_tht);
            printf("========================\n");
            printf("Silakan menuju Poli THT dan menunggu panggilan\n");
            break;
        case 0:
            return;
        default:
            printf("Pilihan tidak valid!\n");
            pause();
            pilihPoli();
            return;
    }
    pause();
}

void prosesLoketAntrian() {
    int pilihan;
    tampilkanHeader("PROSES LOKET ANTRIAN");
    
    if(current_antrian_masuk == 0) {
        printf("Tidak ada antrian saat ini\n");
        pause();
        return;
    }
    
    printf("Memanggil antrian nomor: %d\n", 1);
    printf("Pasien dipanggil...\n\n");
    
    printf("Status Pasien:\n");
    printf("1. Pasien Baru\n");
    printf("2. Pasien Lama\n");
    printf("\nPilihan: ");
    scanf("%d", &pilihan);
    
    switch(pilihan) {
        case 1:
            inputDataPasienBaru();
            pilihPoli();
            break;
        case 2:
            cariPasienLama();
            pilihPoli();
            break;
        default:
            printf("Pilihan tidak valid!\n");
            pause();
            return;
    }
    
    // Update antrian setelah diproses
    current_antrian_masuk--;
    if(current_antrian_masuk < 0) current_antrian_masuk = 0;
}

void menuLoketAntrian() {
    int pilihan;
    do {
        tampilkanHeader("LOKET ANTRIAN");
        
        printf("1. Proses Antrian\n");
        printf("2. Lihat Status Antrian\n");
        printf("0. Kembali ke Menu Utama\n");
        printf("\nPilihan: ");
        scanf("%d", &pilihan);
        
        switch(pilihan) {
            case 1:
                prosesLoketAntrian();
                break;
            case 2:
                lihatAntrianMasuk();
                break;
            case 0:
                break;
            default:
                printf("Pilihan tidak valid!\n");
                pause();
        }
    } while(pilihan != 0);
}

// ============= MODUL PASIEN POLI =============
void lihatAntrianPoli() {
    int pilihan;
    tampilkanHeader("STATUS ANTRIAN POLI");
    
    printf("Pilih Poli:\n");
    printf("1. Poli Umum\n");
    printf("2. Poli Gigi\n");
    printf("3. Poli THT\n");
    printf("0. Kembali\n");
    printf("\nPilihan: ");
    scanf("%d", &pilihan);
    
    switch(pilihan) {
        case 1:
            printf("\n=== STATUS ANTRIAN POLI UMUM ===\n");
            printf("Total Antrian: %d\n", antrian_poli_umum);
            printf("Antrian Sekarang: %d\n", current_poli_umum);
            printf("Antrian Selanjutnya: %d\n", current_poli_umum + 1);
            break;
        case 2:
            printf("\n=== STATUS ANTRIAN POLI GIGI ===\n");
            printf("Total Antrian: %d\n", antrian_poli_gigi);
            printf("Antrian Sekarang: %d\n", current_poli_gigi);
            printf("Antrian Selanjutnya: %d\n", current_poli_gigi + 1);
            break;
        case 3:
            printf("\n=== STATUS ANTRIAN POLI THT ===\n");
            printf("Total Antrian: %d\n", antrian_poli_tht);
            printf("Antrian Sekarang: %d\n", current_poli_tht);
            printf("Antrian Selanjutnya: %d\n", current_poli_tht + 1);
            break;
        case 0:
            return;
        default:
            printf("Pilihan tidak valid!\n");
            pause();
            lihatAntrianPoli();
            return;
    }
    pause();
}

// ============= MODUL DOKTER =============
void inputDataKunjungan() {
    tampilkanHeader("INPUT DATA KUNJUNGAN");
    
    printf("=== Data Kunjungan Pasien ===\n");
    printf("Pasien: John Doe (NIK: 1234567890123456)\n");
    printf("Tanggal: [Tanggal Otomatis]\n\n");
    
    printf("Keluhan: [Input Keluhan]\n");
    printf("Diagnosa: [Input Diagnosa]\n");
    printf("Resep: [Input Resep]\n");
    printf("Biaya Pemeriksaan: [Input Biaya]\n");
    
    printf("\nData kunjungan berhasil disimpan!\n");
    printf("Data tagihan telah dikirim ke bagian pembayaran.\n");
    
    pause();
}

void panggilPasien(int poli) {
    char namaPoli[20];
    int *currentAntrian;
    
    switch(poli) {
        case 1:
            strcpy(namaPoli, "UMUM");
            currentAntrian = &current_poli_umum;
            break;
        case 2:
            strcpy(namaPoli, "GIGI");
            currentAntrian = &current_poli_gigi;
            break;
        case 3:
            strcpy(namaPoli, "THT");
            currentAntrian = &current_poli_tht;
            break;
        default:
            return;
    }
    
    tampilkanHeader("PANGGIL PASIEN");
    
    printf("Memanggil pasien antrian nomor %d di Poli %s\n", *currentAntrian, namaPoli);
    printf("Pasien sedang menuju ruang pemeriksaan...\n");
    
    for(int i = 5; i > 0; i--) {
        printf("Menunggu pasien (%d detik)\n", i);
        sleep(1);
        if(i > 1) {
            printf("\033[1A\033[K"); // Clear line and move cursor up
        }
    }
    
    printf("\nPasien telah masuk ruang pemeriksaan.\n");
    pause();
    
    inputDataKunjungan();
    
    // Update antrian setelah pasien dipanggil
    (*currentAntrian)++;
}

void menuDokter() {
    int pilihan, poli;
    
    do {
        tampilkanHeader("MENU DOKTER");
        
        printf("Pilih Poli Anda:\n");
        printf("1. Dokter Poli Umum\n");
        printf("2. Dokter Poli Gigi\n");
        printf("3. Dokter Poli THT\n");
        printf("0. Kembali ke Menu Utama\n");
        printf("\nPilihan: ");
        scanf("%d", &poli);
        
        if(poli == 0) break;
        if(poli < 1 || poli > 3) {
            printf("Pilihan tidak valid!\n");
            pause();
            continue;
        }
        
        do {
            char judulPoli[50];
            switch(poli) {
                case 1: strcpy(judulPoli, "DOKTER POLI UMUM"); break;
                case 2: strcpy(judulPoli, "DOKTER POLI GIGI"); break;
                case 3: strcpy(judulPoli, "DOKTER POLI THT"); break;
            }
            
            tampilkanHeader(judulPoli);
            
            printf("1. Panggil Pasien\n");
            printf("2. Lihat Status Antrian\n");
            printf("0. Kembali\n");
            printf("\nPilihan: ");
            scanf("%d", &pilihan);
            
            switch(pilihan) {
                case 1:
                    panggilPasien(poli);
                    break;
                case 2:
                    lihatAntrianPoli();
                    break;
                case 0:
                    break;
                default:
                    printf("Pilihan tidak valid!\n");
                    pause();
            }
        } while(pilihan != 0);
        
    } while(poli != 0);
}

// ============= MODUL PEMBAYARAN =============
void prosesPembayaran() {
    float biaya, bayar, kembalian;
    
    tampilkanHeader("PROSES PEMBAYARAN");
    
    printf("=== Data Tagihan ===\n");
    printf("Pasien: John Doe\n");
    printf("Poli: Umum\n");
    printf("Dokter: Dr. Smith\n");
    printf("Biaya Pemeriksaan: Rp 150,000\n");
    printf("===================\n\n");
    
    biaya = 150000; // Contoh biaya dari dokter
    
    printf("Total Biaya: Rp %.0f\n", biaya);
    printf("Uang yang diterima: Rp ");
    scanf("%f", &bayar);
    
    if(bayar < biaya) {
        printf("Uang tidak cukup!\n");
        pause();
        return;
    }
    
    kembalian = bayar - biaya;
    
    printf("\n=== STRUK PEMBAYARAN ===\n");
    printf("Total Biaya: Rp %.0f\n", biaya);
    printf("Uang Diterima: Rp %.0f\n", bayar);
    printf("Kembalian: Rp %.0f\n", kembalian);
    printf("========================\n");
    printf("Pembayaran berhasil!\n");
    
    pause();
}

void menuPembayaran() {
    int pilihan;
    
    do {
        tampilkanHeader("BAGIAN PEMBAYARAN");
        
        printf("1. Proses Pembayaran\n");
        printf("2. Lihat Daftar Tagihan\n");
        printf("0. Kembali ke Menu Utama\n");
        printf("\nPilihan: ");
        scanf("%d", &pilihan);
        
        switch(pilihan) {
            case 1:
                prosesPembayaran();
                break;
            case 2:
                printf("=== DAFTAR TAGIHAN ===\n");
                printf("1. John Doe - Rp 150,000 (Belum Bayar)\n");
                printf("2. Jane Smith - Rp 200,000 (Belum Bayar)\n");
                pause();
                break;
            case 0:
                break;
            default:
                printf("Pilihan tidak valid!\n");
                pause();
        }
    } while(pilihan != 0);
}

// ============= MENU UTAMA =============
void menuUtama() {
    int pilihan;
    
    do {
        tampilkanHeader("MENU UTAMA");
        
        printf("=== UNTUK PASIEN ===\n");
        printf("1. Ambil Antrian\n");
        printf("2. Lihat Status Antrian Masuk\n");
        printf("3. Lihat Status Antrian Poli\n\n");
        
        printf("=== UNTUK PETUGAS ===\n");
        printf("4. Loket Antrian\n");
        printf("5. Dokter\n");
        printf("6. Pembayaran\n\n");
        
        printf("0. Keluar\n");
        printf("\nPilihan: ");
        scanf("%d", &pilihan);
        
        switch(pilihan) {
            case 1:
                ambilAntrian();
                break;
            case 2:
                lihatAntrianMasuk();
                break;
            case 3:
                lihatAntrianPoli();
                break;
            case 4:
                menuLoketAntrian();
                break;
            case 5:
                menuDokter();
                break;
            case 6:
                menuPembayaran();
                break;
            case 0:
                tampilkanHeader("TERIMA KASIH");
                printf("Sistem Administrasi Rumah Sakit ditutup.\n");
                printf("Terima kasih telah menggunakan sistem kami.\n");
                exit(0);
                break;
            default:
                printf("Pilihan tidak valid!\n");
                pause();
        }
    } while(pilihan != 0);
}

int main() {
    printf("Memulai Sistem Administrasi Rumah Sakit...\n");
    sleep(2);
    
    menuUtama();
    
    return 0;
}