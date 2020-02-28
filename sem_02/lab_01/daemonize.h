#ifndef __DAEMONIZE_H
#define __DAEMONIZE_H

#include <stdlib.h>
#include <signal.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>

void daemonize(const char *cmd);

#endif /* __DAEMONIZE_H */
