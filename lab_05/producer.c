#include "producer.h"

void producer(int* shared_bufer, const int len, const int semid)
{
    int i;

    for (i = 0; i < len; ++i)
    {
        sleep(1);

        if (semop(semid, take_semafor_producer, 2) == -1)
            semop_error();

        shared_bufer[i] = i + 1;
        printf("Producer write %d\n", i + 1);

        if (semop(semid, free_semafor_producer, 2) == -1)
            semop_error();
    }

    exit(0);
}
