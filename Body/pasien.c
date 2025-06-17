/*Implementasi fungsi tambah pasien, cari pasien (BST), riwayat kunjungan*/
#ifndef PASIEN_C
#define PASIEN_C

#include "../header.h"


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

#endif