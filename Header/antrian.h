/*modul untuk antrian dan layanan poli menggunakan queue 
 Fungsi:
- Ambil antrian layanan ( maksimal 20/hari)
- Lihat antrian berjalan 
- Data struktur: Queue dengan array atau linked list
*/

#ifndef ANTRIAN_H
#define ANTRIAN_H

#include "queueLayanan.h"

void menuAntrianLayanan(Queue *antrian);
void tampilkanStatusAntrian(Queue *antrian);

#endif