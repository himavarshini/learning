#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

char *string = NULL;

void *thread_func(void *th)
{
    while (1) {
        printf("Waiting .. %s\n", __func__);
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        printf("Locked .. %s\n", __func__);
        printf("string is %s\n", string);
        free(string);
        pthread_mutex_unlock(&mutex);
        printf("Unlocked .. %s\n", __func__);
    }
}

int main(void)
{
    pthread_t tid;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&tid, NULL, thread_func, NULL);

    while (1) {
        printf("Waiting.. %s\n", __func__);
        pthread_mutex_lock(&mutex);
        string = calloc(1, 200);
        printf("Locked .. %s\n", __func__);
        strcpy(string, "a very very very big string...");
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        printf("Unlocked.. %s\n", __func__);
//        usleep(1000 * 1000);
    }

    return 0;
}

