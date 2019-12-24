#include "writer.h"

void writer(int* shared_bufer, const int semid)
{
    while(1)
    {
        sleep(2);

        if (semop(semid, take_semafor_writer, 4) == -1)
            semop_error();

        ++(*shared_bufer);
        printf("Writer [%d] --> %d\n", getpid(), *shared_bufer);

        if (semop(semid, free_semafor_writer, 1) == -1)
            semop_error();
    }
}
