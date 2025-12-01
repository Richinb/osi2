#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define SUCCESS 0
#define ERROR -1
#define NOT_EQUAL 0
#define NUM_THREADS 5

int global_var = 100;

void *mythread(void *arg)
{
    pid_t pid = getpid();
    pid_t ppid = getppid();
    pid_t tid_from_gettid = gettid();
    pthread_t tid_from_create = *(pthread_t *)arg;
    pthread_t tid_from_self = pthread_self();

    int local_var = 2;
    static int static_local_var = 3;
    const int const_local_var = 4;
    printf("mythread [%d %d %d]: Hello from mythread!\n", pid, ppid, tid_from_gettid);
    printf("mythread ID (pthread_self): %lu\n", tid_from_self);
    printf("Thread ID from pthread_create: %lu\n", tid_from_create);

    if (pthread_equal(tid_from_create, tid_from_self) != NOT_EQUAL)
    {
        printf("pthread_self() and pthread_create() ID are EQUAL\n");
    }
    if (pthread_equal(tid_from_create, tid_from_self) == NOT_EQUAL)
    {
        printf("pthread_self() and pthread_create() ID are DIFFERENT\n");
    }

    if (pthread_equal(tid_from_create, tid_from_gettid) != NOT_EQUAL)
    {
        printf("gettid() and pthread_create() ID are EQUAL\n");
    }
    if (pthread_equal(tid_from_create, tid_from_gettid) == NOT_EQUAL)
    {
        printf("gettid() and pthread_create() ID are DIFFERENT\n");
    }

    printf("Addresses:\n");
    printf("  Local variable: %p\n", (void *)&local_var);
    printf("  Static local variable: %p\n", (void *)&static_local_var);
    printf("  Const local variable: %p\n", (void *)&const_local_var);
    printf("  Global variable: %p\n", (void *)&global_var);

    return NULL;
}

int main()
{
    pthread_t tid[NUM_THREADS];
    pthread_t *ptr_to_tids = tid;
    int err;

    printf("main [%d %d %d]: Hello from main!\n", getpid(), getppid(), gettid());
    for (int i = 0; i < NUM_THREADS; i++)
    {
        printf("\nThread %d: \n", i);
        err = pthread_create(&tid[i], NULL, mythread, (void *)&ptr_to_tids[i]);
        if (err != SUCCESS)
        {
            printf("main: pthread_create() failed: %s\n", strerror(err));
            return ERROR;
        }
    }

    pthread_exit(NULL);
}
