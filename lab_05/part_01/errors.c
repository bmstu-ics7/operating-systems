#include "errors.h"

void fork_error()
{
    perror("Can't fork\n");
    exit(-1);
}

void shget_error()
{
    perror("Can't create shared memory\n");
    exit(-2);
}

void shmat_error()
{
    perror("Can't get memory\n");
    exit(-3);
}

void semget_error()
{
    perror("Can't create semaphore\n");
    exit(-4);
}

void semctl_error()
{
    perror("Can't control semaphor\n");
    exit(-5);
}

void semop_error()
{
    perror("Can't operate semafor\n");
    exit(-6);
}

void clean_error()
{
    perror("Can't clean\n");
    exit(-7);
}
