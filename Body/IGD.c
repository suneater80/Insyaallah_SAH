#include "../Header/IGD.h"
#include "../Header/queue.h"


IGDQueue igdQueue;

void initIGD(IGDQueue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
    q->nomorTerakhir = 0;
}

void daftarPoliIGD(Poli *poli) {
    poli->nomorTerakhirIGD++;
    enqueuePoli(&poli->antrianIGD, poli->nomorTerakhirIGD);
    printf("[PRIORITAS IGD] Nomor IGD-%d untuk %s\n", poli->nomorTerakhirIGD, poli->nama);
}

void daftarIGD(IGDQueue *q) {
    q->nomorTerakhir++;
    q->rear = (q->rear + 1) % MAX_IGD;
    q->nomorAntrian[q->rear] = q->nomorTerakhir;
    q->count++;
    printf("Pendaftaran IGD Biasa berhasil! Nomor: %d\n", q->nomorTerakhir);
}

void prosesIGDBiasa(IGDQueue *q, Poli poli[]) {
    if (q->count == 0) {
        printf("Tidak ada pasien IGD Biasa.\n");
        return;
    }

    printf("Pasien IGD-%d sedang diperiksa...\n", q->nomorAntrian[q->front]);
    sleep(2);

    printf("Pilih Poli Rujukan: 1. Umum 2. Gigi 3. THT\nPilihan: ");
    int p;
    scanf("%d", &p);
    if (p >= 1 && p <= MAX_POLI) {
        daftarPoliIGD(&poli[p - 1]);
    } else {
        printf("Poli tidak valid.\n");
    }

    q->front = (q->front + 1) % MAX_IGD;
    q->count--;
}

void prosesEmergencyIGD(Poli poli[]) {
    printf("Pasien IGD Emergency sedang diperiksa...\n");
    sleep(2);
    printf("Pemeriksaan selesai.\n");
}

void lihatStatusIGD(IGDQueue *q) {
    printf("Total IGD Biasa: %d\n", q->count);
    if (q->count > 0) printf("Sedang Dilayani: IGD-%d\n", q->nomorAntrian[q->front]);
}

void layananIGD(Poli poli[]) {
    static int initialized = 0;
    if (!initialized) { initIGD(&igdQueue); initialized = 1; }

    int pilihan;
    do {
        clearScreen();
        tampilkanHeader("LAYANAN IGD");
        printf("1. Daftar IGD Biasa\n2. Daftar IGD Emergency\n3. Proses IGD Biasa\n4. Status IGD\n0. Kembali\nPilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: daftarIGD(&igdQueue); pause(); break;
            case 2: prosesEmergencyIGD(poli); pause(); break;
            case 3: prosesIGDBiasa(&igdQueue, poli); pause(); break;
            case 4: lihatStatusIGD(&igdQueue); pause(); break;
            case 0: break;
            default: printf("Pilihan tidak valid.\n"); pause();
        }
    } while (pilihan != 0);
}
