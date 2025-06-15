#include "../Header/poli.h"

// ============= MODUL PASIEN POLI =============
int main() {
    Poli poli[MAX_POLI];
    initPoli(poli);
    
    int pilihan;
  
    
    do {
        tampilkanHeader("MENU UTAMA POLI");
        printf("1. Daftar Antrian Poli\n");
        printf("2. Proses Antrian Poli\n");
        printf("3. Lihat Status Antrian Poli\n");
        printf("0. Keluar\n");
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
                printf("Terima kasih!\n");
                break;

            default:
                printf("Pilihan tidak valid!\n");
                pause();
        }

    } while (pilihan != 0);
       return 0;
}