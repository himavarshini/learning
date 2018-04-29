#include <stdio.h>
#include <pthread.h>

pthread_cond_t cond;
pthread_mutex_t mutex;

int i;

void *thread_wait(void *data)
{

	for (;;) {
		pthread_mutex_lock(&mutex);
		printf("waiting\n");
		pthread_cond_wait(&cond, &mutex);
		printf("value of i is %d\n", i);
		// here the thread sleeps for 20 seconds
		// taking the mutex lock and thus the main
		// thread awaits in a loop until this guy
		// releases the lock for it
		sleep(20);
		pthread_mutex_unlock(&mutex);
	}
}

int main(void)
{
	pthread_t tid;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
	pthread_create(&tid, NULL, thread_wait, NULL);
	sleep(10);
	for (i = 0; i < 1100; i++) {
		if (i >= 6) {
			pthread_mutex_lock(&mutex);
			pthread_cond_signal(&cond);
			pthread_mutex_unlock(&mutex);
		}
		sleep(1);
		printf("value of i will be %d\n", i);
	}

	return 0;
}

