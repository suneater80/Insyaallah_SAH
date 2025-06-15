#include <stdio.h>
#include "../Header/antrian.h"
#include "../Header/queue.h"

void tampilkanMenuUtama() {
    printf("=== SISTEM ANTRIAN KLINIK ===\n");
    printf("1. Ambil Antrian Layanan\n");
    printf("2. Lihat Status Antrian\n");
    printf("3. Keluar\n");
    printf("Pilih menu: ");
}

int main() {
    Queue antrianLayanan;
    initQueue(&antrianLayanan);

    int pilihan;
    do {
        tampilkanMenuUtama();
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                menuAntrianLayanan(&antrianLayanan);
                break;
            case 2:
                tampilkanStatusAntrian(&antrianLayanan);
                break;
            case 3:
                printf("Terima kasih telah menggunakan sistem antrian.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
                getchar(); getchar();
                break;
        }

    } while (pilihan != 3);

    return 0;
}
