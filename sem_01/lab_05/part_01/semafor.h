#ifndef __SEMAFOR_H
#define __SEMAFOR_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>

#define P -1
#define V +1

#define SB 0
#define SE 1
#define SF 2

typedef struct sembuf sembuf;

sembuf take_semafor_producer[2];
sembuf free_semafor_producer[2];
sembuf take_semafor_consumer[2];
sembuf free_semafor_consumer[2];

#endif /* __SEMAFOR_H */
