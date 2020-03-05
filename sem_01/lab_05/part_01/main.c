#include <unistd.h>
#include <sys/shm.h>
#include <signal.h>
#include "consumer.h"
#include "producer.h"

#define COUNT 3
#define N 8
#define PERM  S_IRWXU | S_IRWXG | S_IRWXO

int main(void)
{
    pid_t producers[COUNT];
    pid_t consumers[COUNT];
    int status, shmid, semid, ctrl_sb, ctrl_se, ctrl_sf, i;
    int* shared_bufer;

    shmid = shmget(IPC_PRIVATE, (N + 2) * sizeof(int), IPC_CREAT | PERM);

    if (shmid == -1)
        shget_error();

    shared_bufer = shmat(shmid, 0, 0);

    if (*((int*)shared_bufer) == -1)
        shmat_error();

    semid = semget(IPC_PRIVATE, 3, IPC_CREAT | PERM);

    if (semid == -1)
        semget_error();

    ctrl_sb = semctl(semid, SB, SETVAL, 1);
    ctrl_se = semctl(semid, SE, SETVAL, N);
    ctrl_sf = semctl(semid, SF, SETVAL, 0);

    if (ctrl_sb == -1 || ctrl_se == -1 || ctrl_sf == -1)
        semctl_error();

    *shared_bufer = 2;
    *(shared_bufer + 1) = 2;

    for (i = 0; i < COUNT; ++i)
    {
        producers[i] = fork();

        if (producers[i] == -1)
            fork_error();
        else if (producers[i] == 0)
            producer(shared_bufer, N, semid);

        consumers[i] = fork();

        if (consumers[i] == -1)
            fork_error();
        else if (consumers[i] == 0)
            consumer(shared_bufer, N, semid);

        sleep(2);
    }

    for (i = 0; i < COUNT; ++i)
    {
        wait(&status);
        wait(&status);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1)
        clean_error();

    if (semctl(semid, 0, IPC_RMID, 0) == -1)
        clean_error();

    return 0;
}
