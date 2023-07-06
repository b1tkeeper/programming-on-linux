#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void *worker_func(void *args)
{
    pthread_t tid = pthread_self();
    printf("Executed by thread %ld\n", (unsigned long)tid);
    srand(time(NULL));
    double num = (double)rand() / RAND_MAX;
    for (size_t i = 0; i < 1000000000; i++)
    {
        sqrt(num);
    }
    return "ok";
}

int main(int argc, char const *argv[])
{
    int workers = 10;
    pthread_t group[workers];
    for (size_t i = 0; i < workers; i++)
    {
        pthread_create(&group[i], NULL, worker_func, NULL);
    }

    for (size_t i = 0; i < workers; i++)
    {
        void *thread_result;
        pthread_join(group[i], &thread_result);
    }

    return 0;
}
