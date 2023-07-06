#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_FILE "myfifo"

int main(int argc, char const *argv[])
{
    char *msg = "Hello, FIFO!";
    char buffer[BUFSIZ];

    // create fifo file
    if (mkfifo(FIFO_FILE, 0666) != 0)
    {
        perror("Failed to create fifo file");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    int rfd, wfd;

    if (pid == 0)
    {
        wfd = open(FIFO_FILE, O_WRONLY);
        if (wfd == -1)
        {
            perror("Failed to open fifo in child process");
            exit(EXIT_FAILURE);
        }
        write(wfd, msg, strlen(msg) - 1);
        close(wfd);

        // unlink
        unlink(FIFO_FILE);
    }
    else
    {
        rfd = open(FIFO_FILE, O_RDONLY);
        if (rfd == -1)
        {
            perror("Failed to open fifo in parent process");
            exit(EXIT_FAILURE);
        }
        read(rfd, buffer, BUFSIZ);
        close(rfd);
        printf("Received message in parent: %.*s\n", BUFSIZ, buffer);
    }
    return 0;
}
