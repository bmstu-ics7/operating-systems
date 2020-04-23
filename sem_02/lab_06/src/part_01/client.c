#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "error.h"

#define SIZE_BUFFER 100

int sockfd;

void close_app()
{
    if (close(sockfd) < 0)
        exit(error());

    exit(0);
}

int main()
{
    size_t len;
    struct sockaddr srvr_name;
    char *buffer;
    char message[SIZE_BUFFER];

    signal(SIGINT, close_app);

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);

    if (sockfd < 0)
        return error();

    srvr_name.sa_family = AF_UNIX;
    strcpy(srvr_name.sa_data, "socket.soc");

    while(1)
    {
        printf("Type message: ");
        getline(&buffer, &len, stdin);
        sprintf(message, "[%d] : %s", getpid(), buffer);
        sendto(sockfd, message, strlen(message), 0, &srvr_name, strlen(srvr_name.sa_data) + sizeof(srvr_name.sa_family) + 1);
    }

    return 0;
}
