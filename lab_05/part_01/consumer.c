#include "consumer.h"

void consumer(int* shared_bufer, const int len, const int semid)
{
    while(1)
    {
        sleep(1);

        if (semop(semid, take_semafor_consumer, 2) == -1)
            semop_error();

        printf("Consumer [%d] <-- %d\n", getpid(), *(shared_bufer + *(shared_bufer + 1)));

        (*(shared_bufer + 1))++;

        if (semop(semid, free_semafor_consumer, 2) == -1)
            semop_error();

        if (*(shared_bufer + 1) >= len - 1)
        {
            *(shared_bufer + 1) = 2;
        }
    }

    exit(0);
}
