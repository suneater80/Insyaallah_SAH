#include "header.h"

void menuPoli(Poli poli[]);

int main() {
    QueueLayanan antrianLayanan;
    Poli daftarPoli[MAX_POLI];
    int pilihan;
    
    // Inisialisasi
    initQueueLayanan(&antrianLayanan);
    initPoli(daftarPoli);
    
    do {
        clearScreen();
        tampilkanHeader("SISTEM ANTRIAN RUMAH SAKIT");
        
        printf("1. Ambil Antrian Layanan\n");
        printf("2. Lihat Status Antrian Layanan\n");
        printf("3. Menu Loket Antrian (Petugas)\n");
        printf("4. Manajemen Poli\n");
        printf("0. Keluar\n");
        printf("\nPilihan: ");
        scanf("%d", &pilihan);
        
        switch(pilihan) {
            case 1:
                menuAntrianLayanan(&antrianLayanan);
                break;
            case 2:
                tampilkanStatusAntrian(&antrianLayanan);
                break;
            case 3:
                menuLoketAntrian(&antrianLayanan);
                break;
            case 4:
                menuPoli(daftarPoli);
                break;
            case 0:
                printf("Terima kasih telah menggunakan sistem antrian!\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
                pause();
        }
    } while(pilihan != 0);
    
    return 0;
}

// Fungsi tambahan untuk menu poli
void menuPoli(Poli poli[]) {
    int pilihan, poliPilihan;
    
    do {
        clearScreen();
        tampilkanHeader("MANAJEMEN POLI");
        
        printf("1. Daftar ke Poli\n");
        printf("2. Proses Antrian Poli\n");
        printf("3. Lihat Status Antrian Poli\n");
        printf("0. Kembali ke Menu Utama\n");
        printf("\nPilihan: ");
        scanf("%d", &pilihan);
        
        switch(pilihan) {
            case 1:
                printf("\nPilih Poli:\n");
                for(int i = 0; i < MAX_POLI; i++) {
                    printf("%d. %s\n", i+1, poli[i].nama);
                }
                printf("Pilihan: ");
                scanf("%d", &poliPilihan);
                
                if(poliPilihan >= 1 && poliPilihan <= MAX_POLI) {
                    daftarPoli(&poli[poliPilihan-1]);
                } else {
                    printf("Pilihan tidak valid!\n");
                }
                pause();
                break;
                
            case 2:
                printf("\nPilih Poli untuk diproses:\n");
                for(int i = 0; i < MAX_POLI; i++) {
                    printf("%d. %s (Antrian: %d)\n", i+1, poli[i].nama, getCountPoli(&poli[i].antrian));
                }
                printf("Pilihan: ");
                scanf("%d", &poliPilihan);
                
                if(poliPilihan >= 1 && poliPilihan <= MAX_POLI) {
                    prosesAntrianPoli(&poli[poliPilihan-1]);
                } else {
                    printf("Pilihan tidak valid!\n");
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
    } while(pilihan != 0);
}