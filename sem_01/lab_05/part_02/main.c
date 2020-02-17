#include <unistd.h>
#include <sys/shm.h>
#include <signal.h>
#include "writer.h"
#include "reader.h"

#define COUNT 3
#define PERM  S_IRWXU | S_IRWXG | S_IRWXO

int main(void)
{
    pid_t writers[COUNT];
    pid_t readers[COUNT];
    int status, shmid, semid, ctrl, i;
    int* shared_bufer;

    shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | PERM);

    if (shmid == -1)
        shget_error();

    shared_bufer = shmat(shmid, 0, 0);

    if (*shared_bufer == -1)
        shmat_error();

    *shared_bufer = 0;

    semid = semget(IPC_PRIVATE, 4, IPC_CREAT | PERM);

    if (semid == -1)
        semget_error();

    ctrl = semctl(semid, ACTIVE_WRITER, SETVAL, 1);

    if (ctrl == -1)
        semctl_error();

    for (i = 0; i < COUNT; ++i)
    {
        writers[i] = fork();

        if (writers[i] == -1)
            fork_error();
        else if (writers[i] == 0)
            writer(shared_bufer, semid);

        readers[i] = fork();

        if (readers[i] == -1)
            fork_error();
        else if (readers[i] == 0)
            reader(shared_bufer, semid);

        sleep(1);
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
