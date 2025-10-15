#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#define THREADS_COUNT 5
#define SUCCESS 0
#define ERROR -1
#define NOT_EQUAL 0

int global_var = 1;

void *mythread(void *arg)
{
    pid_t pid = getpid();
    pid_t ppid = getppid();
    pid_t tid_from_gettid = gettid();

    int local_var = 2;
    static int static_local_var = 3;
    const int const_local_var = 4;
    printf("mythread [%d %d %d]: Hello from mythread!\n", pid, ppid, tid_from_gettid);
    printf("Before: local_var=%d, global_var=%d\n", local_var, global_var);
    local_var++;
    global_var++;
    printf("After: local_var=%d, global_var=%d\n", local_var, global_var);

    printf("\n");

    return NULL;
}

int main()
{
    pthread_t tid[THREADS_COUNT];
    pthread_t *ptr_to_tids = tid;
    int err;

    printf("main [%d %d %d]: Hello from main!\n", getpid(), getppid(), gettid());

    err = pthread_create(&tid, NULL, mythread, (void *)&ptr_to_tids);
    if (err != SUCCESS)
    {
        printf("main: pthread_create() failed: %s\n", strerror(err));
        return ERROR;
    }

    sleep(10);
    return 0;
}
