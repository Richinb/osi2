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
#define NUM_THREADS 5

void *mythread(void *arg)
{
	int thread_num = *(int *)arg;
	printf("Thread %d [%d %d %d]: Hello from mythread!\n", thread_num, getpid(), getppid(), gettid());
	return NULL;
}

int main()
{
	pthread_t tids[NUM_THREADS];
	int thread_nums[NUM_THREADS];
	int err;

	printf("main [%d %d %d]: Creating %d threads\n", getpid(), getppid(), gettid(), NUM_THREADS);

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

	return 0;
}
