#ifndef ANTRIAN_H
#define ANTRIAN_H
#include "header.h"

// Queue
typedef struct QueueNode {
    char namaPasien; // Menyimpan nama pasien yang antri, nanti akan dihapus jika telah antri
    int nomorAntrian; 
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
    int count; // Jumlah pasien dalam antrian
    int lastNomorAntrian; // Untuk generate nomor antrian berikutnya
} Queue;



#endif