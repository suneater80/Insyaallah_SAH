/*modul untuk antrian dan layanan poli menggunakan queue 
 Fungsi:
- Ambil antrian layanan ( maksimal 20/hari)
- Lihat antrian berjalan 
- Proses antrian layanan
- Data struktur: Queue dengan array atau linked list
*/

#ifndef ANTRIAN_H
#define ANTRIAN_H

#include "queue.h"
#include "pasien.h"
#include "poli.h"

void menuAntrianLayanan(QueueLayanan *antrian);
void tampilkanStatusAntrian(QueueLayanan *antrian);
void prosesLoketAntrian(QueueLayanan *antrian, NodePasien** rootPasien, Poli* daftarPoliKlinik); //parsing by value **


// Fungsi helper
void tampilkanHeader(const char *judul);
void pause();
void clearScreen();

#endif