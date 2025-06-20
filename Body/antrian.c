#include "../Header/antrian.h"
#include "../Header/queue.h"

#ifdef _WIN32
#include <windows.h>
#define CLEAR() system("cls")
#else
#include <unistd.h>
#define CLEAR() system("clear")
#endif

void clearScreen() {
    CLEAR();
}

void pause() {
    printf("\nTekan ENTER untuk kembali ke menu...");
    getchar(); 
    getchar();
}

void tampilkanHeader(const char *judul) {
    printf("\n===========================\n");
    printf(" %s\n", judul);
    printf("===========================\n");
}

void menuAntrianLayanan(QueueLayanan *antrian) {
    clearScreen();
    tampilkanHeader("AMBIL ANTRIAN LAYANAN");
    
    if (isFullLayanan(antrian)) {
        printf("Antrian sudah habis untuk hari ini. Terima kasih telah berkunjung.\n");
        pause();
        return;
    }

    printf("Antrian masih tersedia dan Anda akan mengambil antrian.\n");
    printf("Silakan pilih kategori pasien:\n");
    printf("1. Umum\n");
    printf("2. BPJS\n");
    printf("0. Kembali ke Menu Utama\n");
    printf("Pilihan Anda: ");

    int pilihan;
    char input[10];
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &pilihan) != 1) {
        printf("Pilihan tidak valid.\n");
        pause();
        return;
    }

    Kategori kategori;
    switch (pilihan) {
    case 1:
        kategori = UMUM;
        break;
    case 2:
        kategori = BPJS;
        break;
    case 0:
        return;
    default:
        printf("Pilihan tidak valid.\n");
        pause();
        return;
    }

    if (enqueueLayanan(antrian, kategori)) {
        char awalan = (kategori == UMUM) ? 'U' : 'B';
        int nomor = antrian->data[antrian->rear].nomor;
        printf("\nAntrian berhasil diambil\n");
        printf("Nomor Antrian Anda: %c-%02d\n", awalan, nomor);
    } else {
        printf("\nGagal mengambil antrian.\n");
    }

    pause();
}

void tampilkanStatusAntrian(QueueLayanan *antrian) {
    clearScreen();
    tampilkanHeader("STATUS ANTRIAN LAYANAN");

    if (!isEmptyLayanan(antrian)) {
        AntrianLayanan *current = peekLayanan(antrian);
        char awalan = (current->kategori == UMUM) ? 'U' : 'B';
        
        printf("Sedang Dipanggil      : %c-%02d\n", awalan, current->nomor);
        
        // Cek antrian selanjutnya
        if (antrian->count > 1) {
            int nextIndex = (antrian->front + 1) % MAX_ANTRIAN_LAYANAN;
            AntrianLayanan *next = &antrian->data[nextIndex];
            char awalanNext = (next->kategori == UMUM) ? 'U' : 'B';
            printf("Antrian Selanjutnya   : %c-%02d\n", awalanNext, next->nomor);
        } else {
            printf("Antrian Selanjutnya   : -\n");
        }
        
        printf("Sisa Antrian          : %d\n", antrian->count - 1);
        printf("Estimasi Waktu Tunggu : %d menit\n", (antrian->count - 1) * 5);
    } else {
        printf("Tidak ada antrian saat ini.\n");
    }

    pause();
}

void prosesLoketAntrian(QueueLayanan *antrian, NodePasien** rootPasien, Poli* daftarPoliKlinik) {
    int pilihan;
    clearScreen();
    tampilkanHeader("PROSES LOKET ANTRIAN");
    
    if(isEmptyLayanan(antrian)) {
        printf("Tidak ada antrian saat ini\n");
        pause();
        return;
    }
    
    AntrianLayanan *current = peekLayanan(antrian);
    char awalan = (current->kategori == UMUM) ? 'U' : 'B';
    
    printf("Memanggil antrian nomor: %c-%02d\n", awalan, current->nomor);
    printf("Kategori: %s\n", (current->kategori == UMUM) ? "Umum" : "BPJS");
    printf("Pasien dipanggil...\n\n");
    
    printf("Status Pasien:\n");
    printf("1. Pasien Baru\n");
    printf("2. Pasien Lama\n");
    printf("\nPilihan: ");
    
    char input[10];
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &pilihan) != 1) {
        printf("Pilihan tidak valid!\n");
        pause();
        return;
    }

    switch(pilihan) {
        case 1:
        {
            // Tambah Pasien Baru
            printf("\nMemproses pasien baru...\n");
            {
                Pasien newPasien;
                inputDataPasien(&newPasien);
                
                // Validasi NIK tidak kosong
                if (strlen(newPasien.nik) == 0) {
                    tampilkanPesanError("NIK tidak boleh kosong!");
                    break;
                }
                
                // Cek apakah NIK sudah ada
                NodePasien* existing = searchPasien(*rootPasien, newPasien.nik);
                if (existing != NULL) {
                    tampilkanPesanError("Pasien dengan NIK tersebut sudah terdaftar!");
                    break;
                }
                
                *rootPasien = insertPasien(*rootPasien, newPasien);
                tampilkanPesanSukses("Pasien berhasil ditambahkan!");
                tungguEnter();
                break;
            }

            //pasien memilih poli yang dituju
            clearScreen();
            int pilihanPoli;
            tampilkanHeader("DAFTAR ANTRIAN POLI");
            printf("1. Poli Umum\n2. Poli Gigi\n3. Poli THT\nPilihan: ");
            scanf("%d", &pilihanPoli);
            if (pilihanPoli >= 1 && pilihanPoli <= 3)
                daftarPoli(&daftarPoliKlinik[pilihanPoli - 1]);
            else
                    printf("Pilihan tidak valid!\n");
            pause();

            break;
        }
        case 2:
        {
            // Cari Pasien yang telah terdaftar
            printf("\nMemproses pasien lama...\n");
            char* nik = inputNikPasien();
                
            NodePasien* found = searchPasien(*rootPasien, nik);
            if (found != NULL) {
                cetakDataPasien(found->data);
            } else {
                char errorMsg[100];
                sprintf(errorMsg, "Pasien dengan NIK %s tidak ditemukan.", nik);
                tampilkanPesanError(errorMsg);
            }
            tungguEnter();

            //pasien memilih poli yang dituju
            clearScreen();
            int pilihanPoli;
            tampilkanHeader("DAFTAR ANTRIAN POLI");
            printf("1. Poli Umum\n2. Poli Gigi\n3. Poli THT\nPilihan: ");
            scanf("%d", &pilihanPoli);
            if (pilihanPoli >= 1 && pilihanPoli <= 3)
                daftarPoli(&daftarPoliKlinik[pilihanPoli - 1]);
            else
                    printf("Pilihan tidak valid!\n");
            pause();

            break;
        }
        default:
            printf("Pilihan tidak valid!\n");
            pause();
            return;
    }
    
    printf("\nProses selesai. Pasien diarahkan ke poli tujuan.\n");
    
    // Update antrian setelah diproses (dequeue)
    int nomorSelesai = dequeueLayanan(antrian);
    printf("Antrian nomor %c-%02d telah selesai diproses.\n", awalan, nomorSelesai);
    
    if (!isEmptyLayanan(antrian)) {
        AntrianLayanan *next = peekLayanan(antrian);
        char awalanNext = (next->kategori == UMUM) ? 'U' : 'B';
        printf("Antrian selanjutnya: %c-%02d\n", awalanNext, next->nomor);
    } else {
        printf("Semua antrian telah selesai diproses.\n");
    }
    
    pause();
}

