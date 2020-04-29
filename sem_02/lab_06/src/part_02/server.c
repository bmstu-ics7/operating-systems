#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <netinet/in.h>
#include <signal.h>
#include "error.h"

#define SIZE_BUFFER 100
#define CLIENTS 100

int sockfd;
int maxi, maxfd;
int pid_client[CLIENTS];

void close_signal()
{
    if (close(sockfd) < 0)
        exit(error());

    printf("\nSocket closed\n");
    exit(0);
}

int connection(int client[FD_SETSIZE], fd_set *allset, fd_set *rset)
{
    int i = 0;
    int connfd;
    int message_len;
    char buffer[SIZE_BUFFER];

    if (FD_ISSET(sockfd, rset))
    {
        connfd = accept(sockfd, NULL, NULL);

        if (connfd < 0)
            return errno;

        do
        {
            if (client[i] < 0)
                client[i] = connfd;
            i++;
        }
        while(client[i] >= 0);

        if (i == FD_SETSIZE)
            return errno;

        FD_SET(connfd, allset);

        if (connfd > maxfd)
            maxfd = connfd;

        if (i > maxi)
            maxi = i;

        message_len = read(connfd, buffer, SIZE_BUFFER);
        pid_client[i] = atoi(buffer);
        printf("[%d] connected\n", pid_client[i]);
    }

    return 0;
}

int message(int client[FD_SETSIZE], fd_set *allset, fd_set *rset)
{
    int n, i;
    int sockfd;
    char buffer[SIZE_BUFFER];

    for (i = 0; i <= maxi; i++)
    {
        sockfd = client[i];
        if (sockfd > 0)
        {
            if (FD_ISSET(sockfd, rset))
            {
                n = read(sockfd, buffer, SIZE_BUFFER);

                if (n == 0)
                {
                    close(sockfd);
                    FD_CLR(sockfd, allset);
                    client[i] = -1;
                    printf("[%d] disconnected\n", pid_client[i]);
                }
                else
                {
                    write(sockfd, "good", 4);
                    printf("[%d] : %s", pid_client[i], buffer);
                }
            }
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return -1;
    }

    int client[FD_SETSIZE];
    fd_set rset;
    fd_set allset;
    struct sockaddr_in server;

    signal(SIGINT, close_signal);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        return errno;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    bind(sockfd, (struct sockaddr *) &server, sizeof(server));

    if (errno != 0)
        return errno;

    listen(sockfd, CLIENTS);

    maxfd = sockfd;
    maxi = -1;

    for (int i = 0; i < FD_SETSIZE; i++)
        client[i] = -1;

    FD_ZERO(&allset);
    FD_SET(sockfd, &allset);

    printf("Socket is successfully opened\n");
    printf("Press Ctrl+C to close this application\n");

    while(1)
    {
        rset = allset;
        select(maxfd + 1, &rset, NULL, NULL, NULL);

        connection(client, &allset, &rset);

        if (errno != 0)
            return error();

        message(client, &allset, &rset);

        if (errno != 0)
            return error();
    }

    return 0;
}
