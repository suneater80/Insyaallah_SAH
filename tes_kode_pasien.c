#include "header.h"



int main() {
    NodePasien* root = NULL;
    int pilihan;
    char filename[] = "dataPasien.txt";
    
    // Load data dari file saat startup
    printf("=== SISTEM MANAJEMEN PASIEN ===\n");
    printf("Memuat data...\n");
    root = loadPasienFromFile(filename);
    
    do {
        pilihan = tampilkanMenu();
        
        switch (pilihan) {
            case 1: {
                // Tambah Pasien Baru
                Pasien newPasien;
                inputDataPasien(&newPasien);
                
                // Validasi NIK tidak kosong
                if (strlen(newPasien.nik) == 0) {
                    tampilkanPesanError("NIK tidak boleh kosong!");
                    break;
                }
                
                // Cek apakah NIK sudah ada
                NodePasien* existing = searchPasien(root, newPasien.nik);
                if (existing != NULL) {
                    tampilkanPesanError("Pasien dengan NIK tersebut sudah terdaftar!");
                    break;
                }
                
                root = insertPasien(root, newPasien);
                tampilkanPesanSukses("Pasien berhasil ditambahkan!");
                tungguEnter();
                break;
            }
            
            case 2: {
                // Cari Pasien
                char* nik = inputNikPasien();
                
                NodePasien* found = searchPasien(root, nik);
                if (found != NULL) {
                    cetakDataPasien(found->data);
                } else {
                    char errorMsg[100];
                    sprintf(errorMsg, "Pasien dengan NIK %s tidak ditemukan.", nik);
                    tampilkanPesanError(errorMsg);
                }
                tungguEnter();
                break;
            }
            
            case 3: {
                // Tambah Kunjungan
                char* nik = inputNikPasien();
                
                NodePasien* found = searchPasien(root, nik);
                if (found != NULL) {
                    char tanggal[11], keluhan[100], diagnosa[100], resep[200], dokter[50];
                    float biaya;
                    
                    inputDataKunjungan(tanggal, keluhan, diagnosa, resep, dokter, &biaya);
                    
                    tambahKunjungan(&found->data, tanggal, keluhan, diagnosa, resep, dokter, biaya);
                    tampilkanPesanSukses("Kunjungan berhasil ditambahkan!");
                } else {
                    char errorMsg[100];
                    sprintf(errorMsg, "Pasien dengan NIK %s tidak ditemukan.", nik);
                    tampilkanPesanError(errorMsg);
                }
                tungguEnter();
                break;
            }
            
            case 4: {
                // Cetak Rekam Medis
                char* nik = inputNikPasien();
                
                NodePasien* found = searchPasien(root, nik);
                if (found != NULL) {
                    cetakDataPasien(found->data);
                } else {
                    char errorMsg[100];
                    sprintf(errorMsg, "Pasien dengan NIK %s tidak ditemukan.", nik);
                    tampilkanPesanError(errorMsg);
                }
                tungguEnter();
                break;
            }
            
            case 5: {
                // Lihat Semua Pasien
                printf("\n=== DAFTAR SEMUA PASIEN ===\n");
                if (root == NULL) {
                    printf("Belum ada pasien yang terdaftar.\n");
                } else {
                    cetakSemuaPasien(root);
                }
                tungguEnter();
                break;
            }
            
            case 6: {
                // Simpan Data
                saveAllPasienToFile(root, filename);
                tungguEnter();
                break;
            }
            
            case 0: {
                // Keluar
                printf("\nMenyimpan data sebelum keluar...\n");
                saveAllPasienToFile(root, filename);
                tampilkanPesanSukses("Data telah disimpan. Terima kasih!");
                break;
            }
            
            default:
                tampilkanPesanError("Pilihan tidak valid!");
                tungguEnter();
        }
    } while (pilihan != 0);
    
    // Free memory sebelum keluar
    freeBstPasien(root);
    
    return 0;
}