#include <stdio.h>
#include <sys/types.h>

int main()
{
    pid_t childpid1, childpid2;

    childpid1 = fork();

    if (childpid1 == -1)
    {
        perror("Can’t fork.\n");
        return 1;
    }
    else if (childpid1 == 0)
    {
        printf("CHILD1\npid: %d; ppid: %d; gid: %d\n\n", getpid(), getppid(), getgid());
        getchar();
        printf("CHILD1\npid: %d; ppid: %d; gid: %d\n\n", getpid(), getppid(), getgid());
        return 0;
    }

    childpid2 = fork();

    if (childpid2 == -1)
    {
        perror("Can't fork.\n");
        return 1;
    }
    else if (childpid2 == 0)
    {
        printf("CHILD2\npid: %d; ppid: %d; gid: %d\n\n", getpid(), getppid(), getgid());
        getchar();
        printf("CHILD2\npid: %d; ppid: %d; gid: %d\n\n", getpid(), getppid(), getgid());
        return 0;
    }
    else
    {
        printf("PARENT\npid: %d; ppid: %d; gid: %d\n\n", getpid(), getppid(), getgid());
        getchar();
    }

    return 0;
}
