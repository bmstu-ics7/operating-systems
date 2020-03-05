#include "already_running.h"

int already_running(void)
{
    int fd;
    char buf[16];

    fd = open(LOCKFILE, O_RDWR | O_CREAT, LOCKMODE);

    if (fd < 0)
    {
        return(-1);
    }

    flock(fd, LOCK_EX | LOCK_NB);

	if (errno == EWOULDBLOCK)
    {
        return(-1);
    }

    ftruncate(fd, 0);
    sprintf(buf, "%ld", (long)getpid());
    write(fd, buf, strlen(buf) + 1);
    return(0);
}
