/* Implementasi fungsi balancing BST Pasien */
#include "../header.h"

// ===== IMPLEMENTASI FUNGSI BALANCING =====

// Fungsi untuk menghitung jumlah node dalam BST
int countNodes(NodePasien* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Fungsi untuk melakukan inorder traversal dan menyimpan node ke array
void inorderToArray(NodePasien* root, NodePasien** arr, int* index) {
    if (root == NULL) {
        return;
    }
    
    // Traversal inorder: left -> root -> right
    inorderToArray(root->left, arr, index);
    
    // Simpan node ke array (hanya pointer ke node, bukan copy data)
    arr[*index] = root;
    (*index)++;
    
    inorderToArray(root->right, arr, index);
}

// Fungsi untuk membangun balanced BST dari sorted array
NodePasien* buildBalancedBST(NodePasien** arr, int start, int end) {
    if (start > end) {
        return NULL;
    }
    
    // Pilih middle element sebagai root
    int mid = start + (end - start) / 2;
    NodePasien* root = arr[mid];
    
    // Reset pointer left dan right
    root->left = NULL;
    root->right = NULL;
    
    // Rekursif untuk subtree kiri dan kanan
    root->left = buildBalancedBST(arr, start, mid - 1);
    root->right = buildBalancedBST(arr, mid + 1, end);
    
    return root;
}

// Fungsi utama untuk menyeimbangkan BST
NodePasien* balanceBST(NodePasien* root) {
    if (root == NULL) {
        printf("Tree kosong, tidak perlu balancing.\n");
        return NULL;
    }
    
    printf("Memulai proses balancing BST...\n");
    
    // Hitung jumlah node
    int nodeCount = countNodes(root);
    printf("Jumlah node dalam tree: %d\n", nodeCount);
    
    if (nodeCount <= 1) {
        printf("Tree hanya memiliki 1 atau 0 node, sudah balanced.\n");
        return root;
    }
    
    // Alokasi array untuk menyimpan pointer ke node
    NodePasien** nodeArray = (NodePasien**)malloc(nodeCount * sizeof(NodePasien*));
    if (nodeArray == NULL) {
        printf("Error: Memory allocation failed untuk balancing\n");
        return root;
    }
    
    // Lakukan inorder traversal untuk mendapatkan sorted array
    int index = 0;
    inorderToArray(root, nodeArray, &index);
    
    // Bangun balanced BST dari sorted array
    NodePasien* balancedRoot = buildBalancedBST(nodeArray, 0, nodeCount - 1);
    
    // Free array (bukan node-nya, karena masih digunakan)
    free(nodeArray);
    
    printf("Balancing BST selesai.\n");
    printf("Tinggi tree sebelum balancing: %d\n", getTreeHeight(root));
    printf("Tinggi tree setelah balancing: %d\n", getTreeHeight(balancedRoot));
    
    return balancedRoot;
}

// Fungsi untuk melakukan preorder traversal (untuk verifikasi)
void preorderTraversal(NodePasien* root) {
    if (root == NULL) {
        return;
    }
    
    printf("NIK: %s, Nama: %s\n", root->data.nik, root->data.nama);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Fungsi untuk menghitung tinggi tree (untuk debugging)
int getTreeHeight(NodePasien* root) {
    if (root == NULL) {
        return 0;
    }
    
    int leftHeight = getTreeHeight(root->left);
    int rightHeight = getTreeHeight(root->right);
    
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Fungsi tambahan untuk memverifikasi bahwa BST property masih terpenuhi
int verifyBST(NodePasien* root, char* minNik, char* maxNik) {
    if (root == NULL) {
        return 1; // Empty tree is valid BST
    }
    
    // Check if current node violates BST property
    if ((minNik != NULL && strcmp(root->data.nik, minNik) <= 0) ||
        (maxNik != NULL && strcmp(root->data.nik, maxNik) >= 0)) {
        return 0;
    }
    
    // Recursively check left and right subtrees
    return verifyBST(root->left, minNik, root->data.nik) &&
           verifyBST(root->right, root->data.nik, maxNik);
}

// Fungsi helper untuk memverifikasi BST (wrapper)
int isBST(NodePasien* root) {
    return verifyBST(root, NULL, NULL);
}