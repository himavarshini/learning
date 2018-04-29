#include <stdio.h>
#include <pthread.h>

pthread_cond_t cond;
pthread_mutex_t mutex;

int i;

void *thread_wait(void *data)
{
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    printf("value of i is %d\n", i);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(void)
{
    pthread_t tid;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_create(&tid, NULL, thread_wait, NULL);
    for (i = 0; i < 11; i++) {
        if (i == 6) {
            pthread_cond_signal(&cond);
        }
        sleep(1);
        printf("value of i will be %d\n", i);
    }

    return 0;
}

