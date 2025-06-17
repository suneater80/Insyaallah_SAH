/* Modul list & proses pembayaran pasien
*/

#ifndef PEMBAYARAN_H
#define PEMBAYARAN_H

#include "../header.h"

typedef struct Pembayaran {
    char NIK[20];
    char nama[50];
    char poli[10];
    char status_BPJS[10];
    int biaya;
    struct Pembayaran *next;
} Pembayaran;

void tambahAntrianPembayaran(Pembayaran **head, Pembayaran data);
void prosesPembayaran(Pembayaran **head);
void menuPembayaran(NodePasien* rootPasien, Pembayaran **headPembayaran);

#endif