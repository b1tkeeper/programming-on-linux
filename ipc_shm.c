#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main(int argc, char const *argv[])
{
    key_t key = ftok(".", 'a');
    if (key == -1)
    {
        perror("Failed to call ftok");
        exit(EXIT_FAILURE);
    }

    int shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0)
    {
        perror("Failed to call shmget");
        exit(EXIT_FAILURE);
    }

    char *shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1)
    {
        perror("Failed to call shmat");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        snprintf(shmaddr, SHM_SIZE, "Hello from child process!");
    }
    else
    {
        sleep(1);
        printf("Message from child process is %s\n", shmaddr);
    }

    if (shmdt(shmaddr) == -1)
    {
        perror("Failed to call shmdt");
        exit(EXIT_FAILURE);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("Failed to call shmctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
