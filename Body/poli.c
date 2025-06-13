/*Implementasi fungsi proses antrian poli*/
#ifndef POLI_C
#define POLI_C

#include "../header.h"

// Fungsi inisialisasi daftar Poli
void initPoli(Poli poli[]) {
    char kodePoli[MAX_POLI] = {'U', 'G', 'T'};
    char *namaPoli[MAX_POLI] = {"Poli Umum", "Poli Gigi", "Poli THT"};

    for (int i = 0; i < MAX_POLI; i++) {
        poli[i].kode = kodePoli[i];
        strcpy(poli[i].nama, namaPoli[i]);
        initQueue(&poli[i].antrian); // inisialisasi antrian poli 
    }
}

// Fungsi untuk menampilkan menu pemilihan Poli. Fungsi ini akan memanggil prosesAntrianPoli()
void menuAntrianPoli(Poli daftarPoli[], Pasien *root, Pembayaran **headPembayaran) {
    int pilihan;
    printf("ANTRIAN POLI\n");
    printf("Silakan pilih:\n");
    printf("1.Poli Umum\n");
    printf("2.Poli Gigi\n");
    printf("3.Poli THT\n");
    printf("Pilihan: ");
    scanf("%d", &pilihan);
    getchar(); // membersihkan newline

    if (pilihan < 1 || pilihan > MAX_POLI) {
        printf("Pilihan tidak valid.\n");
        return;
    }

    prosesAntrianPoli(&daftarPoli[pilihan - 1], root, headPembayaran);
}

// Fungsi proses antrian Poli
/*
- mengeluarkan pasien pertama dari antrian (dequeue)
- mencari data pasien di BST berdasarkan nik 
- meminta input untuk data kunjungan 
- menghitung biaya (sesuai poli dan statu bpjs)
- memasukkan pasien ke daftar pembayaran 
*/
void prosesAntrianPoli(Poli *poli, Pasien *root, Pembayaran **headPembayaran){
    if (isEmptyQueue(&poli->antrian)) {
        printf("Tidak ada pasien dalam antrian %s.\n", poli->nama);
        return;
    }

    Pasien dataPasien = dequeue(&poli->antrian); // ✅ UPDATE: gunakan Pasien dataPasien = dequeue(...);

    if (strcmp(dataPasien.nik, "-") == 0) { // ✅ TAMBAH: validasi kalau kosong
        printf("Tidak ada pasien dalam antrian %s.\n", poli->nama);
        return;
    }

    printf("⏳ Memproses antrian pertama di %s...\n", poli->nama);
    printf(" telah dilakukan tindak oleh dokter.\n", dataPasien.nama);

    printf("(Menunggu 5 detik...)\n");
    sleep(5); // simulasi proses tindakan dokter 

    Pasien *pasienBST = cariPasien(root, dataPasien.nik); // cari data pasien di BST 
    if (pasienBST != NULL) {
        tambahKunjungan(pasienBST); // minta input kunjungan pasien
    } else {
        printf("Data pasien tidak ditemukan di database!\n");
        return;
    }

    Pembayaran pembayaran;
    strcpy(pembayaran.NIK, dataPasien.nik);
    strcpy(pembayaran.nama, dataPasien.nama);
    strcpy(pembayaran.poli, poli->nama);
    strcpy(pembayaran.status_BPJS, dataPasien.statusBpjs);
    
    // Simulasi Penentuan biaya berdasarkan BPJS dan jenis poli
    if (strcmp(pembayaran.status_BPJS, "Ya") == 0) {
        pembayaran.biaya = 0;
    } else {
        if (poli->kode == 'U') pembayaran.biaya = 30000;
        else if (poli->kode == 'G') pembayaran.biaya = 50000;
        else if (poli->kode == 'T') pembayaran.biaya = 45000;
    }

    tambahAntrianPembayaran(headPembayaran, pembayaran); // masukkan ke antrian pembayaran 

    printf("➡ Pasien masuk ke daftar pembayaran.\n");
    printf("Tekan Enter untuk lanjut...");
    getchar();
}


#endif