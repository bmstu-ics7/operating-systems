#include "producer.h"

void producer(int* shared_bufer, const int len, const int semid)
{
    while(1)
    {
        sleep(1);

        if (semop(semid, take_semafor_producer, 2) == -1)
            semop_error();

        *(shared_bufer + *shared_bufer) = *shared_bufer - 1;

        printf("Produser [%d] --> %d\n", getpid(), *(shared_bufer + *shared_bufer));

        (*shared_bufer)++;

        if (semop(semid, free_semafor_producer, 2) == -1)
            semop_error();

        if (*shared_bufer >= len - 1)
        {
            *shared_bufer = 2;
        }
    }

    exit(0);
}
