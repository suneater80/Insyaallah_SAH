#include <stdio.h>
#include "Header/poli.h"
#include "Header/queue.h"

// ============= MODUL PASIEN POLI =============
int main() {
    Poli poli[MAX_POLI]; // Array untuk menyimpan semua poli
    initPoli(poli); // Inisialisasi nama poli & queue antriannya
    
    int pilihan;
  
    
    do {
        tampilkanHeader("MENU UTAMA POLI");
        printf("1. Daftar Antrian Poli\n");
        printf("2. Proses Antrian Poli\n");
        printf("3. Lihat Status Antrian Poli\n");
        printf("0. Kembali ke Menu Utama\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tampilkanHeader("DAFTAR ANTRIAN POLI");
                printf("1. Poli Umum\n2. Poli Gigi\n3. Poli THT\nPilihan: ");
                scanf("%d", &pilihan);
                if (pilihan >= 1 && pilihan <= 3)
                    daftarPoli(&poli[pilihan - 1]);
                else
                    printf("Pilihan tidak valid!\n");
                pause();
                break;

            case 2:
                tampilkanHeader("PROSES ANTRIAN POLI");
                printf("1. Poli Umum\n2. Poli Gigi\n3. Poli THT\nPilihan: ");
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
                // printf("Terima kasih!\n");
                // Tidak tampilkan apa-apa, langsung keluar menu poli
                break;

            default:
                printf("Pilihan tidak valid!\n");
                pause();
        }

    } while (pilihan != 0);
       return 0;
}

// Sementara, untuk uji coba mandiri
// int main() {
//     menuPoli(); // Nanti ini dipanggil dari program utama puskesmas
//     return 0;
// }

//Fungsi menuPoli() tidak perlu dipanggil dari main() lagi.

//Nanti dipanggil dari menu utama puskesmas seperti:

// c
// Copy code
// if (pilihan == 3) {
//     menuPoli();
// }