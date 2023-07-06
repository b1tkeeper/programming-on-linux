#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define KEY 1234
#define NUM_PROCESSES 2

void P(int sem_id)
{
    struct sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = -1;
    sem_buf.sem_flg = SEM_UNDO;
    semop(sem_id, &sem_buf, 1);
}

void V(int sem_id)
{
    struct sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = 1;
    sem_buf.sem_flg = SEM_UNDO;
    semop(sem_id, &sem_buf, 1);
}

int main(int argc, char const *argv[])
{
    int sem_id = semget(KEY, 1, IPC_CREAT | 0666);
    if (sem_id == -1)
    {
        perror("Failed to create semaphore");
        exit(1);
    }

    if (semctl(sem_id, 0, SETVAL, 1) == -1)
    {
        perror("Failed to initialize semaphore");
        exit(1);
    }

    pid_t pid;
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            printf("Child process %d waiting...\n", getpid());
            P(sem_id);

            printf("Child process %d acquired the semaphore.\n", getpid());
            sleep(2); // Simulate some work

            V(sem_id);
            printf("Child process %d released the semaphore.\n", getpid());

            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        wait(NULL);
    }

    if (semctl(sem_id, 0, IPC_RMID) == -1)
    {
        perror("Failed to remove semaphore");
        exit(1);
    }
    return 0;
}
