#include "consumer.h"

void consumer(int* shared_bufer, int len, int semid)
{
    int i;

    for (i = 0; i < len; ++i)
    {
        sleep(1);

        if (semop(semid, take_semafor_consumer, 2) == -1)
            semop_error();

        printf("Consumer read %d\n", shared_bufer[i]);

        if (semop(semid, free_semafor_consumer, 2) == -1)
            semop_error();
    }

    exit(0);
}
