#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#define SUCCESS 0
#define ERROR -1
#define NOT_EQUAL 0
#define NUM_THREADS 5

int global_var = 1;

void *mythread(void *arg)
{
    int thread_num = *(int *)arg;
    pid_t pid = getpid();
    pid_t ppid = getppid();
    pid_t tid_from_gettid = gettid();

    int local_var = 2;
    printf("\nThread %d\n", thread_num);
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
    pthread_t tids[NUM_THREADS];
    int thread_nums[NUM_THREADS];
    int err;

    printf("main [%d %d %d]: Hello from main!\n", getpid(), getppid(), gettid());

    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_nums[i] = i;
        err = pthread_create(&tids[i], NULL, mythread, &thread_nums[i]);
        if (err != SUCCESS)
        {
            printf("main: pthread_create() failed for thread %d: %s\n", i, strerror(err));
            return ERROR;
        }
    }

    sleep(10);
    pthread_exit(NULL);
}
