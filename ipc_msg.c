#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_MSG_SIZE 100

typedef struct _Message
{
    long mtype;
    char mtext[MAX_MSG_SIZE];
} Message;

int main(int argc, char const *argv[])
{
    key_t key = ftok("/tmp", 'A');
    if (key == -1)
    {
        perror("Failed to call ftok");
        exit(EXIT_FAILURE);
    }

    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1)
    {
        perror("Failed to call msgget");
        exit(EXIT_FAILURE);
    }

    Message msg;

    pid_t pid = fork();

    if (pid == 0)
    {
        msg.mtype = 1;
        sprintf(msg.mtext, "Hello from child process!");
        if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1)
        {
            perror("Failed to call msgsnd");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0) == -1)
        {
            perror("Failed to call msgrcv");
            exit(EXIT_FAILURE);
        }
        printf("Received msg from child process: %s\n", msg.mtext);
        wait(NULL);
    }

    if (msgctl(msgid, IPC_RMID, NULL) == -1)
    {
        perror("Failed to call msgctl");
        exit(EXIT_FAILURE);
    }
    return 0;
}
