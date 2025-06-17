#include "../Header/IGD.h"
#include "../Header/queue.h"


IGDQueue igdQueue; // Variabel global untuk antrian IGD biasa


// MODUL INISIALISASI QUEUE IGD BIASA 
void initIGD(IGDQueue *q) {
    q->front = 0;         // Awal antrian berada di indeks 0
    q->rear = -1;         // Rear dimulai dari -1 untuk perhitungan antrian circular
    q->count = 0;         // Jumlah pasien awal = 0
    q->nomorTerakhir = 0; // Nomor antrian terakhir = 0
}



// MODUL TAMBAH PASIEN IGD EMERGENCY KE ANTRIAN PRIORITAS POLI 
void daftarPoliIGD(Poli *poli) {
    poli->nomorTerakhirIGD++;                          // Nomor antrian prioritas IGD untuk poli bertambah
    enqueuePoli(&poli->antrianIGD, poli->nomorTerakhirIGD); // Masukkan nomor ke antrian prioritas
    printf("[PRIORITAS IGD] Nomor IGD-%d untuk %s\n", poli->nomorTerakhirIGD, poli->nama); // Tampilkan nomor antrian
}



// MODUL TAMBAH PASIEN IGD BIASA KE ANTRIAN 
void daftarIGD(IGDQueue *q) {
    q->nomorTerakhir++;                             // Tambahkan nomor antrian terakhir
    q->rear = (q->rear + 1) % MAX_IGD;              // Tambahkan rear dengan circular queue
    q->nomorAntrian[q->rear] = q->nomorTerakhir;   // Simpan nomor antrian di rear
    q->count++;                                    // Jumlah antrian bertambah
    printf("Pendaftaran IGD Biasa berhasil! Nomor: %d\n", q->nomorTerakhir); // Tampilkan info pendaftaran
}



// MODUL PROSES PASIEN DARI IGD BIASA --> PILIH RUJUKAN KE POLI 
void prosesIGDBiasa(IGDQueue *q, Poli poli[]) {
    if (q->count == 0) { // Cek apakah antrian kosong
        printf("Tidak ada pasien IGD Biasa.\n");
        return;
    }

    printf("Pasien IGD-%d sedang diperiksa...\n", q->nomorAntrian[q->front]);
    sleep(2); // Simulasi pemeriksaan selama 2 detik

    printf("Pilih Poli Rujukan:");
    printf("1. Umum\n");
    printf("2. Gigi\n");
    printf("3. THT\n");
    printf("Pilihan: ");
    int p;
    scanf("%d", &p);
    if (p >= 1 && p <= MAX_POLI) {
        daftarPoliIGD(&poli[p - 1]); // Masukkan pasien IGD ke antrian prioritas poli sesuai pilihan
    } else {
        printf("Poli tidak valid.\n"); // Tampilkan jika pilihan salah
    }

    q->front = (q->front + 1) % MAX_IGD;// Hapus pasien dari depan antrian
    q->count--; // Kurangi jumlah pasien dalam antrian
}



// MODUL PROSES PASIEN IGD EMERGENCY (langsun tanpa masuk antrian biasa)
void prosesEmergencyIGD(Poli poli[]) {
    printf("Pasien IGD Emergency sedang diperiksa...\n");
    sleep(2); // Simulasi pemeriksaan selama 2 detik
    printf("Pemeriksaan selesai.\n"); // Konfirmasi selesai
}



// MODUL TAMPILKAN STATUS IGD BIASA 
void lihatStatusIGD(IGDQueue *q) {
    printf("Total IGD Biasa: %d\n", q->count); // Jumlah antrian IGD biasa
    if (q->count > 0) printf("Sedang Dilayani: IGD-%d\n", q->nomorAntrian[q->front]); // Tampilkan pasien yang sedang diperiksa
}



// MENU UTAMA LAYANAN IGD 
void layananIGD(Poli poli[]) {
    static int initialized = 0;     // Variabel lokal statis untuk inisialisasi satu kali
    if (!initialized) {             // Jika belum diinisialisasi
        initIGD(&igdQueue);         // Inisialisasi queue IGD biasa
        initialized = 1;            // Tandai sudah diinisialisasi
    }

    int pilihan;
    do {
        clearScreen();                  // Membersihkan layar
        tampilkanHeader("LAYANAN IGD"); // Menampilkan header IGD

        // Tampilkan menu
        printf("1. Daftar IGD Biasa\n");
        printf("2. Daftar IGD Emergency\n");
        printf("3. Proses IGD Biasa\n");
        printf("4. Status IGD\n");
        printf("0. Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan); // Input pilihan menu

        // Eksekusi menu sesuai pilihan
        switch (pilihan) {
            case 1: daftarIGD(&igdQueue); pause(); break;         // Daftar IGD biasa
            case 2: prosesEmergencyIGD(poli); pause(); break;     // IGD emergency
            case 3: prosesIGDBiasa(&igdQueue, poli); pause(); break; // Proses IGD biasa
            case 4: lihatStatusIGD(&igdQueue); pause(); break;    // Status IGD biasa
            case 0: break;                                       // Keluar dari menu
            default: printf("Pilihan tidak valid.\n"); pause();   // Pilihan salah
        }
    } while (pilihan != 0); // Ulangi sampai pengguna memilih keluar
}