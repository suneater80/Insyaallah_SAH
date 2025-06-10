/* Modul list & proses pembayaran pasien
*/

#ifndef PEMBAYARAN_H
#define PEMBAYARAN_H

#include "pasien.h"

typedef struct Pembayaran {
    char NIK[20];
    char nama[MAX_NAMA];
    char poli[10];
    char status_BPJS[10];
    int biaya;
    struct Pembayaran *next;
} Pembayaran;

void tambahAntrianPembayaran(Pembayaran **head, Pembayaran data);
void prosesPembayaran(Pembayaran **head);

#endif