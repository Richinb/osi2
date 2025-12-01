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
#define STRING "hello world"

void *mythread()
{
    printf("mythread [%d %d %d]: Hello from mythread!\n", getpid(), getppid(), gettid());
    char *result = malloc((strlen(STRING) + 1) * sizeof(char));
    if (result == NULL)
    {
        perror("malloc failed");
    }
    strcpy(result, STRING);
    printf("Value to return from mythread: %s\n", result);
    return (void *)result;
}

int main()
{
    pthread_t tid;
    int err;

    err = pthread_create(&tid, NULL, mythread, NULL);
    if (err != SUCCESS)
    {
        printf("main: pthread_create() failed: %s\n", strerror(err));
        return ERROR;
    }

    char *result;
    err = pthread_join(tid, (void **)&result);
    if (err != SUCCESS)
    {
        printf("main: pthread_create() failed: %s\n", strerror(err));
        return ERROR;
    }
    printf("Value from mythread: %s\n", result);
    free(result);
    return SUCCESS;
}
