// Nama file: Body/pembayaran.c

#include "../header.h" // Mengakses semua deklarasi, termasuk dari pembayaran.h ini sendiri

// Data master layanan (masih tetap di sini, karena ini bukan data transaksi)
typedef struct Layanan { // Define struct Layanan lagi di sini atau di header.h
    int id_layanan;
    char nama_layanan[50];
    float biaya;
} Layanan;

Layanan daftar_layanan[] = {
    {101, "Pemeriksaan Umum", 25000.00},
    {102, "Imunisasi", 30000.00},
    {103, "Konsultasi Gizi", 40000.00},
    {104, "Pembersihan Karang Gigi", 75000.00},
    {105, "Tes Darah Lengkap", 50000.00}
};
int jumlah_layanan = sizeof(daftar_layanan) / sizeof(daftar_layanan[0]);

// --- FUNGSI BANTUAN INTERNAL (untuk modul pembayaran ini) ---
void getCurrentDateTime(char *buffer, size_t buffer_size) {
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(buffer, buffer_size, "%Y-%m-%d %H:%M:%S", info);
}

Layanan* cariLayananById(Layanan daftar[], int jumlah_layanan, int id_cari) {
    for (int i = 0; i < jumlah_layanan; i++) {
        if (daftar[i].id_layanan == id_cari) {
            return &daftar[i];
        }
    }
    return NULL;
}

void tampilkanDaftarLayanan(Layanan daftar[], int jumlah_layanan) {
    printf("\n--- Daftar Layanan Puskesmas ---\n");
    printf("----------------------------------\n");
    printf("%-5s %-30s %-10s\n", "ID", "Nama Layanan", "Biaya");
    printf("----------------------------------\n");
    for (int i = 0; i < jumlah_layanan; i++) {
        printf("%-5d %-30s Rp%.2f\n", daftar[i].id_layanan, daftar[i].nama_layanan, daftar[i].biaya);
    }
    printf("----------------------------------\n");
}

// ============= IMPLEMENTASI FUNGSI DARI pembayaran.h ANDA =============

// Implementasi fungsi tambahAntrianPembayaran()
void tambahAntrianPembayaran(Pembayaran **head, Pembayaran data) {
    Pembayaran *newNode = (Pembayaran *)malloc(sizeof(Pembayaran));
    if (newNode == NULL) {
        printf("Gagal mengalokasikan memori untuk pembayaran baru.\n");
        return;
    }

    *newNode = data; // Salin data
    newNode->next = NULL; // Pastikan next-nya NULL

    if (*head == NULL) {
        *head = newNode;
    } else {
        Pembayaran *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    printf("Transaksi pembayaran berhasil ditambahkan ke antrian/list.\n");
}

// Implementasi fungsi prosesPembayaran() (sesuai yang ada di pembayaran.h)
// Asumsi: Fungsi ini akan memproses pembayaran pertama di antrian (dequeue)
void prosesPembayaran(Pembayaran **head) {
    clearScreen();
    tampilkanHeader("MEMPROSES PEMBAYARAN DARI ANTRIAN");

    if (*head == NULL) {
        printf("Antrian pembayaran kosong. Tidak ada yang bisa diproses.\n");
        pause();
        return;
    }

    Pembayaran *toProcess = *head; // Ambil item pertama
    *head = (*head)->next; // Majukan head ke item berikutnya

    printf("Memproses pembayaran untuk:\n");
    printf("  NIK Pasien    : %s\n", toProcess->NIK);
    printf("  Nama Pasien   : %s\n", toProcess->nama);
    printf("  Poli/Layanan  : %s\n", toProcess->poli);
    printf("  Status BPJS   : %s\n", toProcess->status_BPJS);
    printf("  Biaya         : Rp %d\n", toProcess->biaya); // Sesuai int di struct

    printf("\n--- Pembayaran berhasil diproses dari antrian ---\n");

    free(toProcess); // Bebaskan memori node yang sudah diproses
    pause();
}

// ============= FUNGSI MENU UTAMA MODUL PEMBAYARAN DAN HELPERNYA =============

// Fungsi untuk melakukan proses input pembayaran dan menambahkannya ke linked list
void prosesInputPembayaran(NodePasien* rootPasien, Pembayaran **headPembayaran) {
    char nik_input[17];
    NodePasien* node_pasien_ditemukan = NULL;
    Layanan* layanan_terpilih = NULL;
    float biaya_layanan_hitung; // Biaya yang dihitung (float)
    char metode_pembayaran_str[20];
    float bayar, kembalian;
    char current_datetime[20];

    clearScreen();
    tampilkanHeader("INPUT DATA PEMBAYARAN BARU");

    // 1. Input NIK & Cari Pasien di BST
    printf("Masukkan NIK pasien: ");
    scanf("%s", nik_input);
    clearInputBuffer();

    node_pasien_ditemukan = searchPasien(rootPasien, nik_input);

    if (node_pasien_ditemukan == NULL) {
        printf("\nPasien dengan NIK %s tidak ditemukan.\n", nik_input);
        pause();
        return;
    }
    Pasien pasien_data_dari_bst = node_pasien_ditemukan->data;

    printf("\nPasien ditemukan!\n");
    printf("Nama: %s\n", pasien_data_dari_bst.nama);
    printf("Status BPJS: %s\n", pasien_data_dari_bst.statusBpjs);

    // 2. Tampilkan Daftar Layanan & Pilih
    tampilkanDaftarLayanan(daftar_layanan, jumlah_layanan);

    int id_layanan_input;
    printf("\nMasukkan ID Layanan yang dibayar: ");
    scanf("%d", &id_layanan_input);
    clearInputBuffer();

    layanan_terpilih = cariLayananById(daftar_layanan, jumlah_layanan, id_layanan_input);

    if (layanan_terpilih == NULL) {
        printf("Layanan dengan ID %d tidak ditemukan.\n", id_layanan_input);
        pause();
        return;
    }

    // 3. Tentukan Biaya & Metode Pembayaran
    biaya_layanan_hitung = layanan_terpilih->biaya; // Biaya awal
    if (strcmp(pasien_data_dari_bst.statusBpjs, "AKTIF") == 0) {
        strcpy(metode_pembayaran_str, "BPJS");
        printf("\nPasien terdaftar BPJS aktif. Pembayaran akan ditanggung BPJS.\n");
        biaya_layanan_hitung = 0; // Pasien tidak perlu bayar
    } else {
        strcpy(metode_pembayaran_str, "Tunai");
        printf("\nPasien tidak terdaftar BPJS aktif. Pembayaran normal (Tunai).\n");
    }

    // 4. Tampilkan Data Tagihan
    printf("\n=== Data Tagihan ===\n");
    printf("Pasien: %s (NIK: %s)\n", pasien_data_dari_bst.nama, pasien_data_dari_bst.nik);
    printf("Layanan: %s\n", layanan_terpilih->nama_layanan);
    printf("Biaya Layanan Asli: Rp %.2f\n", layanan_terpilih->biaya);
    printf("Metode Pembayaran: %s\n", metode_pembayaran_str);
    if (strcmp(metode_pembayaran_str, "BPJS") == 0) {
        printf("Total Dibayar Pasien: Rp %.2f\n", biaya_layanan_hitung);
    } else {
        printf("Total Biaya (Tunai): Rp %.2f\n", biaya_layanan_hitung);
    }
    printf("===================\n\n");

    // 5. Proses Input Uang (Jika Tunai)
    bayar = 0; kembalian = 0;
    if (strcmp(metode_pembayaran_str, "Tunai") == 0) {
        printf("Uang yang diterima: Rp ");
        scanf("%f", &bayar);
        clearInputBuffer();

        if(bayar < biaya_layanan_hitung) {
            printf("Uang tidak cukup!\n");
            pause();
            return;
        }
        kembalian = bayar - biaya_layanan_hitung;
    } else {
        bayar = biaya_layanan_hitung; // Jika BPJS, anggap uang diterima = biaya (0)
    }

    // 6. Siapkan data Pembayaran sesuai struct temanmu dan panggil tambahAntrianPembayaran
    Pembayaran new_pembayaran_node;
    strcpy(new_pembayaran_node.NIK, pasien_data_dari_bst.nik);
    strcpy(new_pembayaran_node.nama, pasien_data_dari_bst.nama);
    strcpy(new_pembayaran_node.status_BPJS, pasien_data_dari_bst.statusBpjs);
    // Asumsi: poli akan diisi dengan nama layanan yang dibayar
    strcpy(new_pembayaran_node.poli, layanan_terpilih->nama_layanan);
    new_pembayaran_node.biaya = (int)biaya_layanan_hitung; // Penting: cast ke int karena struct Pembayaran memiliki biaya int

    tambahAntrianPembayaran(headPembayaran, new_pembayaran_node); // Panggil fungsi yang baru saja kita implementasikan

    // 7. Tampilkan Struk Pembayaran
    getCurrentDateTime(current_datetime, sizeof(current_datetime));

    clearScreen();
    tampilkanHeader("STRUK PEMBAYARAN");
    printf("Tanggal: %s\n", current_datetime);
    printf("Pasien: %s (NIK: %s)\n", new_pembayaran_node.nama, new_pembayaran_node.NIK);
    printf("Status BPJS: %s\n", new_pembayaran_node.status_BPJS);
    printf("Layanan/Poli: %s\n", new_pembayaran_node.poli);
    printf("Biaya Layanan Asli: Rp %.2f\n", layanan_terpilih->biaya);
    printf("Metode Pembayaran: %s\n", metode_pembayaran_str);

    if (strcmp(metode_pembayaran_str, "BPJS") == 0) {
         printf("Total Dibayar Pasien: Rp %d\n", new_pembayaran_node.biaya);
         printf("Keterangan: Ditanggung BPJS\n");
    } else {
        printf("Total Biaya: Rp %d\n", new_pembayaran_node.biaya);
        printf("Uang Diterima: Rp %.2f\n", bayar);
        printf("Kembalian: Rp %.2f\n", kembalian);
    }
    printf("========================\n");
    printf("Pembayaran berhasil dicatat!\n");

    pause();
}

// Fungsi untuk menampilkan seluruh riwayat pembayaran dari Linked List
void lihatRiwayatPembayaran(Pembayaran *head) { // Menerima head dari Linked List
    clearScreen();
    tampilkanHeader("DAFTAR RIWAYAT PEMBAYARAN");

    if (head == NULL) {
        printf("Belum ada riwayat pembayaran yang tercatat.\n");
    } else {
        printf("%-5s %-18s %-25s %-10s %-18s %-10s\n",
               "No.", "NIK Pasien", "Nama Pasien", "BPJS", "Poli/Layanan", "Biaya");
        printf("----------------------------------------------------------------------------------\n");
        int counter = 1;
        Pembayaran *current = head;
        while (current != NULL) {
            printf("%-5d %-18s %-25s %-10s %-18s Rp%-9d\n",
                   counter++,
                   current->NIK,
                   current->nama,
                   current->status_BPJS,
                   current->poli,
                   current->biaya);
            current = current->next;
        }
        printf("----------------------------------------------------------------------------------\n");
    }
    pause();
}


// Implementasi fungsi menuPembayaran() (sesuai yang kita tambahkan di pembayaran.h)
void menuPembayaran(NodePasien* rootPasien, Pembayaran **headPembayaran) {
    int pilihan;

    do {
        clearScreen();
        tampilkanHeader("BAGIAN PEMBAYARAN");

        printf("1. Input Pembayaran Baru\n"); // Menggantikan "Proses Pembayaran" sebelumnya
        printf("2. Lihat Riwayat Pembayaran\n");
        printf("3. Proses Antrian Pembayaran (Dequeue)\n"); // Fungsi prosesPembayaran() dari pembayaran.h
        printf("0. Kembali ke Menu Utama\n");
        printf("\nPilihan: ");
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid. Masukkan angka.\n");
            clearInputBuffer();
            pilihan = -1;
            pause();
            continue;
        }
        clearInputBuffer();

        switch(pilihan) {
            case 1:
                prosesInputPembayaran(rootPasien, headPembayaran); // Panggil fungsi proses input baru
                break;
            case 2:
                lihatRiwayatPembayaran(*headPembayaran); // Tampilkan riwayat dari linked list
                break;
            case 3:
                prosesPembayaran(headPembayaran); // Panggil fungsi `prosesPembayaran` yang didefinisikan di `pembayaran.h`
                break;
            case 0:
                break;
            default:
                printf("Pilihan tidak valid!\n");
                pause();
        }
    } while(pilihan != 0);
}