#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE (25)

int main(int argc, char const *argv[])
{
    int pipefd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];

    if (pipe(pipefd) == -1)
    {
        perror("Failed to craete pipe\n");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == 0)
    {
        close(pipefd[0]);

        char msg[] = "Hello from child!";
        write(pipefd[1], msg, sizeof(msg));
        close(pipefd[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(pipefd[1]);
        ssize_t numBytes = read(pipefd[0], buffer, BUFFER_SIZE);
        printf("Received message in parent: %.*s\n", (int)numBytes, buffer);
        close(pipefd[0]);
        wait(NULL);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
