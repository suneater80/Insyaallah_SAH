#include "../Header/poli.h"
#include <conio.h>  // Untuk fungsi _kbhit() dan _getch()


// MODUL INISIALISASI DFTAR POLI
void initPoli(Poli poli[]) {
    strcpy(poli[0].nama, "Poli Umum"); // Poli pertama 
    strcpy(poli[1].nama, "Poli Gigi"); // Poli kedua 
    strcpy(poli[2].nama, "Poli THT"); // Poli ketiga 

    for (int i = 0; i < MAX_POLI; i++) {
        initQueuePoli(&poli[i].antrian); // Inisialisasi queue untuk setiap poli 
        poli[i].nomorTerakhir = 0; // Reset nomor antrian 
        poli[i].nomorTerakhirIGD = 0; // Reset nomor antrian IGD 
    }
}



// MODUL DAFTAR PASIEN KE DALAM POLI 
void daftarPoli(Poli *poli) {
    if (isFullPoli(&poli->antrian)) { // cek jika antrian sudah penuh
        printf("Maaf, antrian %s sudah penuh!\n", poli->nama);
        return;
    }
    poli->nomorTerakhir++; // tambahkan nomor antrian 
    enqueuePoli(&poli->antrian, poli->nomorTerakhir); // masukkan ke antrian 
    printf("Pendaftaran berhasil!\nNomor antrian Anda untuk %s: %d\n", poli->nama, poli->nomorTerakhir);
}



// MODUL PROSES ANTRIAN POLI SATU PER SATU 
void prosesAntrianPoli(Poli *poli) {
    if (isEmptyPoli(&poli->antrian)) { // Cek jika antrian kosong
        printf("Tidak ada pasien dalam antrian %s.\n", poli->nama);
        return;
    }

    int nomor = peekPoli(&poli->antrian); // Ambil nomor antrian paling depan
    printf("Pasien nomor %d sedang diperiksa di %s...\n", nomor, poli->nama);
    printf("Tekan ENTER untuk melewati pemeriksaan...\n");

    // Countdown 5 detik, bisa dilewati dengan ENTER
    for (int i = 5; i >= 0; i--) {
        printf("\rSisa waktu: %d detik", i);
        fflush(stdout); // memastikan output langsung tampil/muncul 

        if (_kbhit()) { // Jika ada tombol ditekan
            char c = _getch(); // Ambil input tanpa perlu tekan ENTER
            if (c == '\r') {  // Jika ENTER ditekan, keluar dari countdown '\r' = ENTER
                break;
            }
        }
        sleep(1); // Delay 1 detik 
    }
    printf("\n");  // baris baru setelah countdown selesai
    printf("\nPasien nomor %d selesai diperiksa.\n\n", dequeuePoli(&poli->antrian)); // Keluarkan pasien dari antrian

    // Informasikan status antrian setelah pemeriksaan
    if (isEmptyPoli(&poli->antrian)) {
        printf("Semua pasien di %s telah diperiksa.\n", poli->nama);
    } else {
        printf("Masih ada pasien dalam antrian %s.\n", poli->nama);
    }
}


// MODUL MENAMPILKAN STATUS SELURUH ANTRIAN POLI 
void lihatStatusAntrian(Poli poli[]) {
    clearScreen();
    tampilkanHeader("STATUS ANTRIAN POLI"); // Judul tampilan
    for (int i = 0; i < MAX_POLI; i++) {
        printf("%d. %s\n", i + 1, poli[i].nama);
        printf("   Total Antrian    : %d\n", getCountPoli(&poli[i].antrian));
        printf("   Nomor Terakhir   : %d\n", poli[i].nomorTerakhir);
        if (!isEmptyPoli(&poli[i].antrian))
            printf("   Sedang Dilayani  : %d\n", peekPoli(&poli[i].antrian));
        printf("\n");
    }
    pause(); // Tunggu ENTER untuk kembali ke menu
}



int panggilPoli() {
    Poli poli[MAX_POLI]; // Array untuk menyimpan semua poli
    initPoli(poli); // Inisialisasi nama poli & queue antriannya
    
    int pilihan;

    do {
        clearScreen();
        tampilkanHeader("MENU UTAMA POLI");
        printf("1. Daftar Antrian Poli\n");
        printf("2. Proses Antrian Poli\n");
        printf("3. Lihat Status Antrian Poli\n");
        printf("0. Kembali ke Menu Utama\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                clearScreen();
                tampilkanHeader("DAFTAR ANTRIAN POLI");
                printf("1. Poli Umum\n");
                printf("2. Poli Gigi\n");
                printf("3. Poli THT\n");
                printf("Pilihan: ");
                scanf("%d", &pilihan);
                if (pilihan >= 1 && pilihan <= 3)
                    daftarPoli(&poli[pilihan - 1]);
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
                scanf("%d", &pilihan);
                if (pilihan >= 1 && pilihan <= 3)
                    prosesAntrianPoli(&poli[pilihan - 1]);
                else
                    printf("Pilihan tidak valid!\n");
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
       return 0;
}
