#include "../Header/poli.h"
#include <conio.h>  // Untuk fungsi _kbhit() dan _getch()

// MODUL MENAMPILKAN HEADER MENU
void tampilkanHeader(const char *judul) {
    printf("\n====================================\n");
    printf("       %s\n", judul);
    printf("====================================\n\n");
}



// MODUL INISIALISASI DFTAR POLI
void initPoli(Poli poli[]) {
    strcpy(poli[0].nama, "Poli Umum"); // Poli pertama 
    strcpy(poli[1].nama, "Poli Gigi"); // Poli kedua 
    strcpy(poli[2].nama, "Poli THT"); // Poli ketiga 

    for (int i = 0; i < MAX_POLI; i++) {
        initQueuePoli(&poli[i].antrian); // Inisialisasi queue untuk setiap poli 
        poli[i].nomorTerakhir = 0; // Reset nomor antrian 
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



// MODUL PASUE PROGRAM HINGGA USER TEKAN ENTER 
void pause() {
    printf("\nTekan ENTER untuk melanjutkan...");
    getchar();
    getchar();  // Supaya bisa menangkap newline sisa input sebelumnya
}
