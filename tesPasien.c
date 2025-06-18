#include "header.h"

int main() {
    NodePasien* root = NULL;
    int pilihan;
    char filename[] = "dataPasien.txt";
    
    printf("=== SISTEM MANAJEMEN PASIEN ===\n");
    printf("Memuat data dari file...\n");
    
    // Load data dari file saat program dimulai
    root = loadPasienFromFile(filename);
    
    if (root != NULL) {
        printf("Data berhasil dimuat!\n");
        printf("Jumlah pasien: %d\n", countNodes(root));
        printf("Tinggi BST: %d\n", getTreeHeight(root));
        
        // Verifikasi BST property
        if (isBST(root)) {
            printf("BST property: VALID\n");
        } else {
            printf("BST property: TIDAK VALID - Perlu perbaikan!\n");
        }
    }
    
    do {
        pilihan = tampilkanMenu2();
        
        switch (pilihan) {
            case 1: {
                // Tambah Pasien Baru
                Pasien pasienBaru;
                inputDataPasien(&pasienBaru);
                
                // Cek apakah NIK sudah ada
                NodePasien* existing = searchPasien(root, pasienBaru.nik);
                if (existing != NULL) {
                    tampilkanPesanError("NIK sudah terdaftar!");
                } else {
                    root = insertPasien(root, pasienBaru);
                    tampilkanPesanSukses("Pasien berhasil ditambahkan!");
                }
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
                    tampilkanPesanError("Pasien tidak ditemukan!");
                }
                tungguEnter();
                break;
            }
            
            case 3: {
                // Tambah Kunjungan
                char* nik = inputNikPasien();
                NodePasien* pasienNode = searchPasien(root, nik);
                
                if (pasienNode != NULL) {
                    char tanggal[11], keluhan[100], diagnosa[100], resep[200], dokter[50];
                    float biaya;
                    
                    inputDataKunjungan(tanggal, keluhan, diagnosa, resep, dokter, &biaya);
                    tambahKunjungan(&(pasienNode->data), tanggal, keluhan, diagnosa, resep, dokter, biaya);
                    tampilkanPesanSukses("Kunjungan berhasil ditambahkan!");
                } else {
                    tampilkanPesanError("Pasien tidak ditemukan!");
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
                    tampilkanPesanError("Pasien tidak ditemukan!");
                }
                tungguEnter();
                break;
            }
            
            case 5: {
                // Lihat Semua Pasien
                if (root != NULL) {
                    printf("\n=== DAFTAR SEMUA PASIEN ===\n");
                    cetakSemuaPasien(root);
                } else {
                    tampilkanPesanError("Tidak ada data pasien!");
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
            
            case 7: {
                // Menu Balancing BST
                if (root != NULL) {
                    printf("\n=== INFORMASI BST SAAT INI ===\n");
                    printf("Jumlah node: %d\n", countNodes(root));
                    printf("Tinggi BST: %d\n", getTreeHeight(root));
                    
                    printf("\nApakah Anda ingin melakukan balancing? (y/n): ");
                    char confirm;
                    scanf(" %c", &confirm);
                    clearInputBuffer();
                    
                    if (confirm == 'y' || confirm == 'Y') {
                        root = balanceBST(root);
                        tampilkanPesanSukses("BST berhasil dibalancing!");
                        
                        printf("\n=== INFORMASI BST SETELAH BALANCING ===\n");
                        printf("Tinggi BST: %d\n", getTreeHeight(root));
                        printf("BST valid: %s\n", isBST(root) ? "YA" : "TIDAK");
                    }
                } else {
                    tampilkanPesanError("Tidak ada data untuk dibalancing!");
                }
                tungguEnter();
                break;
            }
            
            case 8: {
                // Statistik BST
                if (root != NULL) {
                    printf("\n=== STATISTIK BST ===\n");
                    printf("Jumlah total node: %d\n", countNodes(root));
                    printf("Tinggi BST: %d\n", getTreeHeight(root));
                    
                    // Hitung tinggi ideal untuk BST seimbang
                    int nodeCount = countNodes(root);
                    int idealHeight = (int)(log2(nodeCount)) + 1;
                    printf("Tinggi ideal (log2(n)): %d\n", idealHeight);
                    
                    int currentHeight = getTreeHeight(root);
                    if (currentHeight > idealHeight * 2) {
                        printf("Status: BST TIDAK SEIMBANG - Disarankan balancing\n");
                    } else {
                        printf("Status: BST cukup seimbang\n");
                    }
                    
                    printf("\n=== TRAVERSAL PREORDER ===\n");
                    printf("(Menampilkan struktur BST saat ini)\n");
                    preorderTraversal(root);
                } else {
                    tampilkanPesanError("Tidak ada data untuk ditampilkan!");
                }
                tungguEnter();
                break;
            }
            
            case 9: {
                // Test Data - Tambah beberapa pasien dummy untuk testing
                printf("\n=== MENAMBAH DATA TEST ===\n");
                
                // Data test
                Pasien testPasien[] = {
                    {"1111111111111111", "Siti Nurhaliza", 31, "P", "Jl. Gatot Subroto No. 4", "081234567893", "AKTIF", NULL, 0},
                    {"1111111111111112", "pentagon xsw", 35, "L", "Jl. Merdeka No. 1", "081234567890", "AKTIF", NULL, 0},
                    {"1111111111111113", "Budi Santoso", 42, "L", "Jl. Thamrin No. 3", "081234567892", "NONAKTIF", NULL, 0},
                    {"1111111111111114", "joko wi dodo", 28, "P", "Jl. Sudirman No. 2", "081234567891", "AKTIF", NULL, 0},
                    {"1111111111111115", "Eko Prasetyo", 39, "L", "Jl. HR Rasuna Said No. 5", "081234567894", "AKTIF", NULL, 0}
                };
                
                int jumlahTest = sizeof(testPasien) / sizeof(testPasien[0]);
                int berhasil = 0;
                
                for (int i = 0; i < jumlahTest; i++) {
                    if (searchPasien(root, testPasien[i].nik) == NULL) {
                        root = insertPasien(root, testPasien[i]);
                        berhasil++;
                    }
                }
                
                printf("Berhasil menambahkan %d pasien test dari %d total\n", berhasil, jumlahTest);
                
                // Tambahkan beberapa kunjungan test
                if (berhasil > 0) {
                    printf("Menambahkan kunjungan test...\n");
                    NodePasien* testNode = searchPasien(root, "1234567890123456");
                    if (testNode != NULL) {
                        tambahKunjungan(&(testNode->data), "2024-01-15", "Demam", "Flu", "Paracetamol", "Dr. Smith", 150000);
                        tambahKunjungan(&(testNode->data), "2024-02-20", "Batuk", "Bronkitis", "Obat Batuk", "Dr. Johnson", 200000);
                    }
                }
                
                tampilkanPesanSukses("Data test berhasil ditambahkan!");
                tungguEnter();
                break;
            }
            
            case 0:
                printf("\nMenyimpan data sebelum keluar...\n");
                saveAllPasienToFile(root, filename);
                printf("Terima kasih telah menggunakan sistem!\n");
                break;
                
            default:
                tampilkanPesanError("Pilihan tidak valid!");
                tungguEnter();
                break;
        }
        
    } while (pilihan != 0);
    
    // Clean up memory
    freeBstPasien(root);
    
    return 0;
}