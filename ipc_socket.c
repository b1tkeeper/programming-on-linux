#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>

#define PORT 8080

int main(int argc, char const *argv[])
{
    struct sockaddr_in serv_addr, client_addr;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Failed to open socket");
        exit(1);
    }

    // init server socket
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Failed to bind server socket");
        exit(1);
    }

    if (listen(sockfd, 5) == -1)
    {
        perror("Failed to listen server socket");
        exit(1);
    }

    socklen_t clilen = sizeof(client_addr);
    while (1)
    {
        int clisock = accept(sockfd, (struct sockaddr *)&client_addr, &clilen);
        if (clisock < 0)
        {
            perror("Failed to accept");
            exit(1);
        }

        pid_t pid = fork();
        if (pid == 0)
        {
            close(sockfd);
            char *msg = "Hello, client!";
            write(clisock, msg, strlen(msg));
            close(clisock);
            exit(EXIT_SUCCESS);
        }
        else
        {
            close(clisock);
        }
    }
    close(sockfd);
    return 0;
}
