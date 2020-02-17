#include "reader.h"

void reader(int* shared_bufer, const int semid)
{
    while(1)
    {
        sleep(1);

        if (semop(semid, take_semafor_reader, 5) == -1)
            semop_error();

        printf("Reader [%d] <-- %d\n", getpid(), *shared_bufer);

        if (semop(semid, free_semafor_reader, 1) == -1)
            semop_error();
    }
}
