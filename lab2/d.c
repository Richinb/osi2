#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

#define SUCCESS 0
#define ERROR -1

void *mythread()
{
    printf("mythread [tid: %d]: Hello from mythread!\n", gettid());
    return NULL;
}

int main()
{

    pthread_t tid;
    int err;
    int counter = 0;

    while (true)
    {
        err = pthread_create(&tid, NULL, mythread, NULL);
        if (err != SUCCESS)
        {
            printf("main: pthread_create() failed: %s\n", strerror(err));
            break;
        }
        counter++;
    }
    printf("%d threads\n", counter);
    return SUCCESS;
}
