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
void prosesAntrianPoli(Poli *poli, NodePasien** rootPasien) {
    if (isEmptyPoli(&poli->antrian)) { // Cek jika antrian kosong
        printf("Tidak ada pasien dalam antrian %s.\n", poli->nama);
        return;
    }

    int nomor = peekPoli(&poli->antrian); // Ambil nomor antrian paling depan
    printf("Pasien nomor %d sedang diperiksa di %s...\n", nomor, poli->nama);
    printf("Tekan ENTER untuk Skip adegan pemeriksaan...\n");

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

    // Input Data Kunjungan    
    printf("Dokter menginput Data Kunjungan Pasien. \n");
    char* nik = inputNikPasien();
                
    NodePasien* found = searchPasien(*rootPasien, nik);
    if (found != NULL) {
        char tanggal[11], keluhan[100], diagnosa[100], resep[200], dokter[50];
        float biaya;
                    
        inputDataKunjungan(tanggal, keluhan, diagnosa, resep, dokter, &biaya);
                    
        tambahKunjungan(&found->data, tanggal, keluhan, diagnosa, resep, dokter, biaya);
        tampilkanPesanSukses("Kunjungan berhasil ditambahkan!");
    } else {
        char errorMsg[100];
        sprintf(errorMsg, "Pasien dengan NIK %s tidak ditemukan.", nik);
        tampilkanPesanError(errorMsg);
    }
    tungguEnter();
    
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
