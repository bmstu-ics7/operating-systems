#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define N 20

void call_signal_int()
{
    printf("Child exit\n");
    exit(0);
}

int main()
{
    int status;
    pid_t childpid1, childpid2;
    char buffer[N];
    char message1[N] = "hello";
    char message2[N] = "goodbye";
    int channel1[2], channel2[2];

    if (pipe(channel1) == -1)
    {
        perror("Cant't pipe.\n");
        return 1;
    }

    childpid1 = fork();

    if (childpid1 == -1)
    {
        perror("Can’t fork.\n");
        return 1;
    }
    else if (childpid1 == 0)
    {
        signal(SIGINT, call_signal_int);

        close(channel1[0]);
        write(channel1[1], message1, sizeof(message1));
        while(1);
    }

    if (pipe(channel2) == -1)
    {
        perror("Cant't pipe.\n");
        return 1;
    }

    childpid2 = fork();

    if (childpid2 == -1)
    {
        perror("Can't fork.\n");
        return 1;
    }
    else if (childpid2 == 0)
    {
        signal(SIGINT, call_signal_int);

        close(channel2[0]);
        write(channel2[1], message2, sizeof(message2));
        while(1);
    }
    else
    {
        signal(SIGINT, SIG_IGN);
        wait(&status);
        if (WIFEXITED(status))
        {
            printf(ANSI_COLOR_GREEN "child process exit success\n" ANSI_COLOR_RESET);

            close(channel1[1]);
            read(channel1[0], buffer, sizeof(buffer));
            printf("message = %s\n", buffer);

            close(channel2[1]);
            read(channel2[0], buffer, sizeof(buffer));
            printf("message = %s\n", buffer);
        }
    }

    return 0;
}
