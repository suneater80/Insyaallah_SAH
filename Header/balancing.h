/* Modul untuk balancing BST Pasien
 * Menggunakan algoritma untuk mengkonversi BST ke balanced BST
 */
#ifndef BALANCING_H
#define BALANCING_H

#include <stdio.h>

// Forward declaration - supaya tidak perlu include pasien.h
typedef struct NodePasien NodePasien;

// ===== DEKLARASI FUNGSI BALANCING =====

// Fungsi untuk menghitung jumlah node dalam BST
int countNodes(NodePasien* root);

// Fungsi untuk melakukan inorder traversal dan menyimpan node ke array
void inorderToArray(NodePasien* root, NodePasien** arr, int* index);

// Fungsi untuk membangun balanced BST dari sorted array
NodePasien* buildBalancedBST(NodePasien** arr, int start, int end);

// Fungsi utama untuk menyeimbangkan BST
NodePasien* balanceBST(NodePasien* root);

// Fungsi untuk melakukan preorder traversal (untuk verifikasi)
void preorderTraversal(NodePasien* root);

// Fungsi untuk menghitung tinggi tree (untuk debugging)
int getTreeHeight(NodePasien* root);

int verifyBST(NodePasien* root, char* minNik, char* maxNik);

int isBST(NodePasien* root);

#endif