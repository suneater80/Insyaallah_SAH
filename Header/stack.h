#ifndef STACK_H
#define STACK_H
#include "header.h"

// Undo jika jadi dibuat
typedef enum {
    OPERASI_TAMBAH_PASIEN,
    OPERASI_UPDATE_REKAM_MEDIS
    // Tambahkan jenis operasi lain jika diperlukan
} JenisOperasi;

typedef struct UndoRedoAction {
    JenisOperasi tipeOperasi;
    void *dataSebelum; // Data sebelum operasi , undo
    void *dataSesudah; // Data sesudah operasi , redo
} UndoRedoAction;

typedef struct StackNode {
    UndoRedoAction aksi;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
} Stack;


#endif