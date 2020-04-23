#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <signal.h>
#include "error.h"

#define SIZE_BUFFER 100

int sockfd;

void close_signal()
{
    if (close(sockfd) < 0)
        exit(error());

    printf("\nSocket closed\n");
    exit(0);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <servername> <port>", argv[0]);
        return -1;
    }

    signal(SIGINT, close_signal);

    struct hostent *server;
    struct sockaddr_in serv_addr;
    char *buffer = NULL;
    size_t len;
    char buffer_server[SIZE_BUFFER];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        return error();

    server = gethostbyname(argv[1]);

    if (server == NULL)
        return error();

    serv_addr.sin_family = AF_INET;
    strncpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
    serv_addr.sin_port = htons(atoi(argv[2]));

    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    if (errno != 0)
        return error();

    buffer = calloc(10, 1);
    sprintf(buffer, "%d", getpid());
    write(sockfd, buffer, strlen(buffer));

    free(buffer);
    buffer = NULL;

    printf("Type message: ");
    getline(&buffer, &len, stdin);
    buffer[len] = '\0';

    while (strcmp(buffer, "exit\n"))
    {
        write(sockfd, buffer, len);

        memset(buffer_server, 0, SIZE_BUFFER);
        read(sockfd, buffer_server, SIZE_BUFFER);
        printf("Message received: %s\n", buffer_server);

        printf("Type message: ");
        getline(&buffer, &len, stdin);
        buffer[len] = '\0';
    }

    return 0;
}
