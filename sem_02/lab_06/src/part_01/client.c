#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "error.h"

#define SIZE_BUFFER 100

int main()
{
    int sockfd;
    size_t len;
    struct sockaddr srvr_name;
    char *buffer;

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);

    if (sockfd < 0)
        return error();

    srvr_name.sa_family = AF_UNIX;
    strcpy(srvr_name.sa_data, "socket.soc");

    printf("Type message: ");
    getline(&buffer, &len, stdin);

    sendto(sockfd, buffer, strlen(buffer), 0, &srvr_name, strlen(srvr_name.sa_data) + sizeof(srvr_name.sa_family) + 1);

    if (close(sockfd) < 0)
        return error();

    return 0;
}
