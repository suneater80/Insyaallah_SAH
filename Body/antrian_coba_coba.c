/*implementasi fungsi antrian layanan*/
#ifndef ANTRIAN_COBA_COBA_C
#define ANTRIAN_COBA_COBA_C

#include "../header.h"

void initQueue(Queue *q) {
    q->depan = -1;
    q->belakang = -1;
}

int isFull(Queue *q) {
    return q->belakang == MAKS_ANTRIAN - 1;
}

int isEmpty(Queue *q) {
    return q->depan == -1 || q->depan > q->belakang;
}

void enqueue(Queue *q) {
    if (isFull(q)) {
        printf("❌ Antrian penuh.\n");
        return;
    }

    if (isEmpty(q)) {
        q->depan = q->belakang = 0;
    } else {
        q->belakang++;
    }

    q->queue[q->belakang].nomor = q->belakang + 1;
}

void dequeue(Queue *q) {
    if (isEmpty(q)) return;
    q->depan++;
    if (q->depan > q->belakang) {
        initQueue(q); // reset queue jika habis
    }
}

int lihatDepan(Queue *q) {
    if (isEmpty(q)) return -1;
    return q->queue[q->depan].nomor;
}

void tampilAntrian(Queue *q) {
    if (isEmpty(q)) {
        printf("Tidak ada antrian.\n");
        return;
    }

    for (int i = q->depan; i <= q->belakang; i++) {
        printf("Antrian ke-%02d\n", q->queue[i].nomor);
    }
}

// === Fungsi untuk CLI kamu ===

void ambilAntrianLayanan(Queue *q) { //
    system("cls||clear");
    printf("▶ AMBIL ANTRIAN LAYANAN\n");

    if (isFull(q)) {
        printf("Antrian sudah habis untuk hari ini. Terima kasih telah berkunjung.\n");
        printf("Tekan Enter untuk kembali ke menu utama...");
        getchar(); getchar(); // dua kali untuk menangkap enter dari scanf sebelumnya
        return;
    }

    printf("Antrian masih tersedia. Ketik \"Y\" untuk konfirmasi dan \"N\" untuk batal: ");
    char konfirmasi;
    scanf(" %c", &konfirmasi);

    if (konfirmasi == 'Y' || konfirmasi == 'y') {
        enqueue(q);
        int nomor = q->queue[q->belakang].nomor;
        printf("✅ Antrian berhasil diambil\n");
        printf("Nomor Antrian Anda: %02d\n", nomor);
    } else {
        printf("❌ Pengambilan antrian dibatalkan.\n");
    }

    printf("Tekan Enter untuk kembali ke menu...");
    getchar(); getchar(); // dua kali enter
}

void lihatAntrianLayanan(Queue *q) {
    system("cls||clear");
    printf("▶ LIHAT ANTRIAN LAYANAN\n");

    if (isEmpty(q)) {
        printf("Belum ada antrian yang diproses hari ini.\n");
    } else {
        int sedang = lihatDepan(q);
        int berikut = (sedang != -1 && sedang < q->queue[q->belakang].nomor) ? sedang + 1 : -1;
        int sisa = q->belakang - q->depan;
        printf("Sedang Dipanggil : %02d\n", sedang);
        if (berikut != -1)
            printf("Antrian Selanjutnya : %02d\n", berikut);
        printf("Sisa antrian : %d\n", sisa);
        printf("Waktu tunggu : %d menit\n", sisa * 5); // opsional waktu tunggu
    }

    printf("Tekan Enter untuk kembali ke menu...");
    getchar(); getchar(); // dua kali enter
}

#endif