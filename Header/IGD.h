#ifndef IGD_H
#define IGD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "poli.h"

#define MAX_IGD 1000 // Maksimal antrian IGD

typedef struct {
    int nomorAntrian[MAX_IGD];
    int front;
    int rear;
    int count;
    int nomorTerakhir;
} IGDQueue;

void initIGD(IGDQueue *q);
void daftarIGD(IGDQueue *q);
void prosesIGDBiasa(IGDQueue *q, Poli poli[]);
void prosesEmergencyIGD(Poli poli[]);
void lihatStatusIGD(IGDQueue *q);
void layananIGD(Poli poli[]);
void daftarPoliIGD(Poli *poli);

#endif
