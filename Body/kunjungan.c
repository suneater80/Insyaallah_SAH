#ifndef KUNJUNGAN_C
#define KUNJUNGAN_C

#include "../header.h"

// Global counter untuk ID kunjungan
int globalKunjunganId = 1;

// ===== IMPLEMENTASI FUNGSI LINKED LIST KUNJUNGAN =====
Kunjungan* createKunjungan(char* tanggal, char* keluhan, char* diagnosa, char* resep, char* dokter, float biaya) {
    Kunjungan* newKunjungan = (Kunjungan*)malloc(sizeof(Kunjungan));
    if (newKunjungan == NULL) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    
    newKunjungan->idKunjungan = globalKunjunganId++;
    strcpy(newKunjungan->tanggal, tanggal);
    strcpy(newKunjungan->keluhan, keluhan);
    strcpy(newKunjungan->diagnosa, diagnosa);
    strcpy(newKunjungan->resep, resep);
    strcpy(newKunjungan->dokter, dokter);
    newKunjungan->biaya = biaya;
    newKunjungan->next = NULL;
    
    return newKunjungan;
}

void tambahKunjungan(Pasien* pasien, char* tanggal, char* keluhan, char* diagnosa, char* resep, char* dokter, float biaya) {
    Kunjungan* newKunjungan = createKunjungan(tanggal, keluhan, diagnosa, resep, dokter, biaya);
    if (newKunjungan == NULL) return;
    
    newKunjungan->next = pasien->riwayat;
    pasien->riwayat = newKunjungan;
    pasien->totalKunjungan++;
}

void cetakRiwayatKunjungan(Kunjungan* head) {
    if (head == NULL) {
        printf("  Belum ada riwayat kunjungan.\n");
        return;
    }
    
    printf("  %-3s %-12s %-20s %-20s %-25s %-15s %-10s\n", 
           "ID", "Tanggal", "Keluhan", "Diagnosa", "Resep", "Dokter", "Biaya");
    printf("  %s\n", "=======================================================================================");
    
    Kunjungan* current = head;
    while (current != NULL) {
        printf("  %-3d %-12s %-20s %-20s %-25s %-15s %.0f\n",
               current->idKunjungan, current->tanggal, current->keluhan,
               current->diagnosa, current->resep, current->dokter, current->biaya);
        current = current->next;
    }
}

void freeRiwayatKunjungan(Kunjungan* head) {
    Kunjungan* current = head;
    while (current != NULL) {
        Kunjungan* temp = current;
        current = current->next;
        free(temp);
    }
}

#endif