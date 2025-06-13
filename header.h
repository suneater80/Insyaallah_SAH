// Include semua header, yang nanti akan dipanggil di body

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>  // untuk sleep()

#include "Header/pasien.h"
#include "Header/antrian.h"
#include "Header/kunjungan.h"
#include "Header/pembayaran.h"
#include "Header/poli.h"
#include "Header/queue.h"
#include "Header/rekamMedis.h"

#include "Body/pasien.c"
#include "Body/InputOutput.c"
#include "Body/antrian.c"
#include "Body/poli.c"
#include "Body/queue.c"



#endif