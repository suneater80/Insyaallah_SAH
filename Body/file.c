#ifndef FILE_C
#define FILE_C

#include "../header.h"

// ===== IMPLEMENTASI FUNGSI FILE OPERATIONS =====
void savePasienToFile(NodePasien* root, FILE* file) {
    if (root == NULL) return;
    
    // Save data pasien
    fprintf(file, "=== PASIEN ===\n");
    fprintf(file, "%s|%s|%d|%s|%s|%s|%s|%d\n",
            root->data.nik, root->data.nama, root->data.usia,
            root->data.jenisKelamin, root->data.alamat, root->data.telepon,
            root->data.statusBpjs, root->data.totalKunjungan);
    
    // Save riwayat kunjungan
    if (root->data.riwayat != NULL) {
        fprintf(file, "=== KUNJUNGAN_%s ===\n", root->data.nik);
        Kunjungan* current = root->data.riwayat;
        while (current != NULL) {
            fprintf(file, "%d|%s|%s|%s|%s|%s|%.0f\n",
                    current->idKunjungan, current->tanggal, current->keluhan,
                    current->diagnosa, current->resep, current->dokter, current->biaya);
            current = current->next;
        }
    }
    fprintf(file, "\n");
    
    // Recursive save untuk subtree
    savePasienToFile(root->left, file);
    savePasienToFile(root->right, file);
}

void saveAllPasienToFile(NodePasien* root, char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file %s\n", filename);
        return;
    }
    
    savePasienToFile(root, file);
    fprintf(file, "=== END ===\n");
    fclose(file);
    printf("Data berhasil disimpan ke %s\n", filename);
}

NodePasien* loadPasienFromFile(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("File %s tidak ditemukan, file baru akan dibuat\n", filename);
        return NULL;
    }
    
    NodePasien* root = NULL;
    char line[500];
    Pasien currentPasien;
    int readingKunjungan = 0;
    
    while (fgets(line, sizeof(line), file)) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        if (strstr(line, "=== PASIEN ===")) {
            readingKunjungan = 0;
            // Read next line for pasien data
            if (fgets(line, sizeof(line), file)) {
                line[strcspn(line, "\n")] = 0;
                
                // Parse pasien data
                char* token = strtok(line, "|");
                strcpy(currentPasien.nik, token);
                token = strtok(NULL, "|");
                strcpy(currentPasien.nama, token);
                token = strtok(NULL, "|");
                currentPasien.usia = atoi(token);
                token = strtok(NULL, "|");
                strcpy(currentPasien.jenisKelamin, token);
                token = strtok(NULL, "|");
                strcpy(currentPasien.alamat, token);
                token = strtok(NULL, "|");
                strcpy(currentPasien.telepon, token);
                token = strtok(NULL, "|");
                strcpy(currentPasien.statusBpjs, token);
                token = strtok(NULL, "|");
                currentPasien.totalKunjungan = atoi(token);
                
                // Initialize riwayat
                currentPasien.riwayat = NULL;
                
                // Insert ke BST
                root = insertPasien(root, currentPasien);
            }
        }
        else if (strstr(line, "=== KUNJUNGAN_")) {
            readingKunjungan = 1;
        }
        else if (readingKunjungan && strlen(line) > 0 && !strstr(line, "===")) {
            // Parse kunjungan data
            int id;
            char tanggal[11], keluhan[100], diagnosa[100], resep[200], dokter[50];
            float biaya;
            
            char* token = strtok(line, "|");
            id = atoi(token);
            token = strtok(NULL, "|");
            strcpy(tanggal, token);
            token = strtok(NULL, "|");
            strcpy(keluhan, token);
            token = strtok(NULL, "|");
            strcpy(diagnosa, token);
            token = strtok(NULL, "|");
            strcpy(resep, token);
            token = strtok(NULL, "|");
            strcpy(dokter, token);
            token = strtok(NULL, "|");
            biaya = atof(token);
            
            // Find pasien and add kunjungan
            NodePasien* pasienNode = searchPasien(root, currentPasien.nik);
            if (pasienNode != NULL) {
                Kunjungan* newKunjungan = createKunjungan(tanggal, keluhan, diagnosa, resep, dokter, biaya);
                if (newKunjungan != NULL) {
                    newKunjungan->idKunjungan = id;
                    newKunjungan->next = pasienNode->data.riwayat;
                    pasienNode->data.riwayat = newKunjungan;
                    
                    // Update global counter
                    if (id >= globalKunjunganId) {
                        globalKunjunganId = id + 1;
                    }
                }
            }
        }
        else if (strstr(line, "=== END ===")) {
            break;
        }
    }
    
    fclose(file);
    printf("Data berhasil dimuat dari %s\n", filename);
    return root;
}



// ===== IMPLEMENTASI FUNGSI INPUT/OUTPUT =====
void inputDataPasien(Pasien* pasien) {
    printf("\n=== INPUT DATA PASIEN BARU ===\n");
    
    printf("NIK (16 digit): ");
    fgets(pasien->nik, sizeof(pasien->nik), stdin);
    pasien->nik[strcspn(pasien->nik, "\n")] = 0;
    
    printf("Nama: ");
    fgets(pasien->nama, sizeof(pasien->nama), stdin);
    pasien->nama[strcspn(pasien->nama, "\n")] = 0;
    
    printf("Usia: ");
    while (scanf("%d", &pasien->usia) != 1) {
        printf("Input tidak valid! Masukkan angka: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    
    printf("Jenis Kelamin (L/P): ");
    fgets(pasien->jenisKelamin, sizeof(pasien->jenisKelamin), stdin);
    pasien->jenisKelamin[strcspn(pasien->jenisKelamin, "\n")] = 0;
    clearInputBuffer();
    
    printf("Alamat: ");
    fgets(pasien->alamat, sizeof(pasien->alamat), stdin);
    pasien->alamat[strcspn(pasien->alamat, "\n")] = 0;
    
    printf("Telepon: ");
    fgets(pasien->telepon, sizeof(pasien->telepon), stdin);
    pasien->telepon[strcspn(pasien->telepon, "\n")] = 0;
    
    printf("Status BPJS (AKTIF/NONAKTIF): ");
    fgets(pasien->statusBpjs, sizeof(pasien->statusBpjs), stdin);
    pasien->statusBpjs[strcspn(pasien->statusBpjs, "\n")] = 0;
    
    // Initialize default values
    pasien->riwayat = NULL;
    pasien->totalKunjungan = 0;
}

void inputDataKunjungan(char* tanggal, char* keluhan, char* diagnosa, char* resep, char* dokter, float* biaya) {
    printf("\n=== INPUT DATA KUNJUNGAN ===\n");
    
    printf("Tanggal kunjungan (YYYY-MM-DD): ");
    fgets(tanggal, 11, stdin);
    tanggal[strcspn(tanggal, "\n")] = 0;
    clearInputBuffer();
    
    printf("Keluhan: ");
    fgets(keluhan, 100, stdin);
    keluhan[strcspn(keluhan, "\n")] = 0;
    
    printf("Diagnosa: ");
    fgets(diagnosa, 100, stdin);
    diagnosa[strcspn(diagnosa, "\n")] = 0;
    
    printf("Resep: ");
    fgets(resep, 200, stdin);
    resep[strcspn(resep, "\n")] = 0;
    
    printf("Dokter: ");
    fgets(dokter, 50, stdin);
    dokter[strcspn(dokter, "\n")] = 0;
    
    printf("Biaya: ");
    while (scanf("%f", biaya) != 1) {
        printf("Input tidak valid! Masukkan angka: ");
        clearInputBuffer();
    }
    clearInputBuffer();
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Deklarasi fungsi input/output eksternal
char* inputNikPasien(void) {
    static char nik[17];
    printf("Masukkan NIK pasien: ");
    fgets(nik, sizeof(nik), stdin);
    nik[strcspn(nik, "\n")] = 0;
    return nik;
}


// ===== TAMBAHAN UNTUK UJI COBA KODE =====
int tampilkanMenu(void) {
    int pilihan;
    
    printf("=============================================\n");
    printf("            SISTEM MANAJEMEN PASIEN          \n");
    printf("=============================================\n\n");

    // Daftar menu utama
    printf("  [1] Tambah Pasien Baru\n");
    printf("  [2] Cari Pasien (berdasarkan NIK)\n");
    printf("  [3] Tambah Kunjungan Pasien\n");
    printf("  [4] Cetak Rekam Medis Pasien\n");
    printf("  [5] Lihat Semua Pasien (Inorder)\n");
    printf("  [6] Simpan Data ke File\n\n");
    
    // Daftar menu tambahan untuk uji Balance
    printf("--- Menu Advanced (Struktur Data) ---\n");
    printf("  [7] Balance BST\n");
    printf("  [8] Statistik & Traversal BST\n");
    printf("  [9] Tambah Data tes DUmmy\n\n");
    
    printf("  [0] Keluar\n");
    printf(" \n");
    printf("Pilihan : ");
    
    while (scanf("%d", &pilihan) != 1) {
        printf("Input tidak valid! Masukkan angka: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    
    return pilihan;
}

void tampilkanPesanSukses(char* pesan) {
    printf("\n=== SUKSES ===\n");
    printf("%s\n", pesan);
}

void tampilkanPesanError(char* pesan) {
    printf("\n=== ERROR ===\n");
    printf("%s\n", pesan);
}

void tungguEnter(void) {
    printf("\nTekan Enter untuk melanjutkan...");
    getchar();
}

#endif