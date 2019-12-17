#include <unistd.h>
#include <sys/shm.h>
#include "consumer.h"
#include "producer.h"

#define N 10
#define PERM  S_IRWXU | S_IRWXG | S_IRWXO

int main(void)
{
    pid_t producer_id, consumer_id;
    int status, shmid, semid, ctrl_sb, ctrl_se, ctrl_sf;
    int* shared_bufer;

    shmid = shmget(IPC_PRIVATE, N * sizeof(int), IPC_CREAT | PERM);

    if (shmid == -1)
        shget_error();

    shared_bufer = shmat(shmid, 0, 0);

    if (*shared_bufer == -1)
        shmat_error();

    semid = semget(IPC_PRIVATE, 3, IPC_CREAT | PERM);

    if (semid == -1)
        semget_error();

    ctrl_sb = semctl(semid, SB, SETVAL, 1);
    ctrl_se = semctl(semid, SE, SETVAL, N);
    ctrl_sf = semctl(semid, SF, SETVAL, 0);

    if (ctrl_sb == -1 || ctrl_se == -1 || ctrl_sf == -1)
        semctl_error();

    producer_id = fork();

    if (producer_id == -1)
        fork_error();
    else if (producer_id == 0)
        producer(shared_bufer, N, semid);

    consumer_id = fork();

    if (consumer_id == -1)
        fork_error();
    else if (consumer_id == 0)
        consumer(shared_bufer, N, semid);

    wait(&status);
    wait(&status);

    if (shmctl(shmid, IPC_RMID, NULL) == -1)
        clean_error();

    if (semctl(semid, 0, IPC_RMID, 0) == -1)
        clean_error();

    return 0;
}
