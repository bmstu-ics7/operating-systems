#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "error.h"

#define SOCK_NAME "socket.soc"
#define SIZE_BUFFER 100
int sockfd;

void close_app()
{
    if (close(sockfd) < 0)
        exit(error());

    if (unlink(SOCK_NAME) < 0)
        exit(error());

    printf("\nSocket closed\n");
    exit(0);
}

int main()
{
    struct sockaddr socket_file;
    struct sockaddr recv_name;
    socklen_t recv_len;
    char buffer[SIZE_BUFFER];
    ssize_t size;

    signal(SIGINT, close_app);

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);

    if (sockfd < 0)
        return error();

    socket_file.sa_family = AF_UNIX;
    strcpy(socket_file.sa_data, SOCK_NAME);
    bind(sockfd, &socket_file, strlen(socket_file.sa_data) + sizeof(socket_file.sa_family) + 1);

    if (errno != 0)
        return error();

    printf("Socket is successfully opened\n");
    printf("Press Ctrl+C to close this application\n");

    while (1)
    {
        size = recvfrom(sockfd, buffer, sizeof(buffer), 0, &recv_name, &recv_len);

        if (size < 0)
            return error();

        buffer[size] = '\0';
        printf("%s", buffer);
    }

    return 0;
}
