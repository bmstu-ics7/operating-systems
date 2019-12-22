#ifndef __SEMAFOR_H
#define __SEMAFOR_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>

#define INC  1
#define ZER  0
#define DEC -1

#define READERS 0
#define WRITERS 1

typedef struct sembuf sembuf;

sembuf take_semafor_writer[2];
sembuf free_semafor_writer[1];
sembuf take_semafor_reader[2];
sembuf free_semafor_reader[1];

#endif /* __SEMAFOR_H */
