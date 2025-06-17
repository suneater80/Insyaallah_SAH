// Include semua header, yang nanti akan dipanggil di body

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

// //Hakim
#include "Header/pasien.h"
#include "Header/kunjungan.h"
#include "Header/file.h"
#include "Header/balancing.h"

#include "Body/balancing.c"
#include "Body/file.c"
#include "Body/kunjungan.c"
#include "Body/pasien.c"

//Azam
#include "Header/antrian.h"

#include "Body/antrian.c"

//Seruni
#include "Header/poli.h"

#include "Body/poli.c"

// Azam & Seruni
#include "Header/queue.h"
#include "Body/queue.c"


#endif