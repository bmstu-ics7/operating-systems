#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

int main()
{
    int status;
    pid_t childpid1, childpid2;

    childpid1 = fork();

    if (childpid1 == -1)
    {
        perror("Can’t fork.\n");
        return 1;
    }
    else if (childpid1 == 0)
    {
        if (execl("/bin/ls", "ls", "-lah", 0) == -1)
        {
            perror("Can't exec.\n");
            exit(1);
        }
    }

    childpid2 = fork();

    if (childpid2 == -1)
    {
        perror("Can't fork.\n");
        return 1;
    }
    else if (childpid2 == 0)
    {
        if (execl("/bin/cat", "cat", "makefile", 0) == -1)
        {
            perror("Can't exec.\n");
            exit(1);
        }
    }
    else
    {
        wait(&status);

        if (WIFEXITED(status)) printf(ANSI_COLOR_GREEN "child process exit success\n" ANSI_COLOR_RESET);
    }

    return 0;
}
