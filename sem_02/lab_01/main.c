#include <stdlib.h>
#include <pthread.h>
#include <syslog.h>
#include <time.h>
#include "daemonize.h"
#include "already_running.h"

sigset_t mask;

int main(int argc, char *argv[])
{
    time_t timer = 0;
    char *cmd;

    cmd = strrchr(argv[0], '/');

    if (cmd == NULL)
        cmd = argv[0];
    else
        cmd++;

    daemonize(cmd);

    if (already_running())
    {
        syslog(LOG_ERR, "демон уже запущен");
        exit(1);
    }

    while(1)
    {
        timer = time(NULL);
        syslog(LOG_INFO, "%d\n", timer);
        sleep(5);
    }

    exit(0);
}
