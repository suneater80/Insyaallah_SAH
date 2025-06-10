/* Menampilkan dan mencetak rekam medis dari file
Fungsi:
- Cetak seluruh data pasien dari file rekam medis
- Data disimpan dalam file rekam_medis.txt (atau lain)
*/
#ifndef REKAMMEDIS_H
#define REKAMMEDIS_H

#include "pasien.h"

void cetakRekamMedis(Pasien *root);
void simpanRekamMedisKeFile(Pasien *root);

#endif
