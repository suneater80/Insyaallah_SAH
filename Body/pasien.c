/*Implementasi fungsi tambah pasien, cari pasien (BST), riwayat kunjungan*/
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

// ===== IMPLEMENTASI FUNGSI BST PASIEN =====
NodePasien* createNodePasien(Pasien pasien) {
    NodePasien* newNode = (NodePasien*)malloc(sizeof(NodePasien));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    
    newNode->data = pasien;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

NodePasien* insertPasien(NodePasien* root, Pasien pasien) {
    if (root == NULL) {
        return createNodePasien(pasien);
    }
    
    int cmp = strcmp(pasien.nik, root->data.nik);
    if (cmp < 0) {
        root->left = insertPasien(root->left, pasien);
    } else if (cmp > 0) {
        root->right = insertPasien(root->right, pasien);
    } else {
        printf("Error: Pasien dengan NIK %s sudah ada!\n", pasien.nik);
        return root;
    }
    
    return root;
}

NodePasien* searchPasien(NodePasien* root, char* nik) {
    if (root == NULL) {
        return NULL;
    }
    
    int cmp = strcmp(nik, root->data.nik);
    if (cmp == 0) {
        return root;
    } else if (cmp < 0) {
        return searchPasien(root->left, nik);
    } else {
        return searchPasien(root->right, nik);
    }
}

void cetakDataPasien(Pasien pasien) {
    printf("\n=== DATA PASIEN ===\n");
    printf("NIK           : %s\n", pasien.nik);
    printf("Nama          : %s\n", pasien.nama);
    printf("Usia          : %d tahun\n", pasien.usia);
    printf("Jenis Kelamin : %s\n", pasien.jenisKelamin);
    printf("Alamat        : %s\n", pasien.alamat);
    printf("Telepon       : %s\n", pasien.telepon);
    printf("Status BPJS   : %s\n", pasien.statusBpjs);
    printf("Total Kunjungan: %d\n", pasien.totalKunjungan);
    printf("\n=== RIWAYAT KUNJUNGAN ===\n");
    cetakRiwayatKunjungan(pasien.riwayat);
}

void cetakSemuaPasien(NodePasien* root) {
    if (root != NULL) {
        cetakSemuaPasien(root->left);
        printf("NIK: %s | Nama: %s | Total Kunjungan: %d\n", 
               root->data.nik, root->data.nama, root->data.totalKunjungan);
        cetakSemuaPasien(root->right);
    }
}

void freeBstPasien(NodePasien* root) {
    if (root != NULL) {
        freeBstPasien(root->left);
        freeBstPasien(root->right);
        freeRiwayatKunjungan(root->data.riwayat);
        free(root);
    }
}

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

