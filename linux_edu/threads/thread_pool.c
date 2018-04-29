#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct thread_work {
    int work;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    struct thread_work *next;
};

void *thread_func(void *ctx)
{
    struct thread_work *work = ctx;

    while (1) {
        pthread_mutex_lock(&work->mutex);
        pthread_cond_wait(&work->cond, &work->mutex);
        printf("woke up doing work .. %d\n", work->work);
        pthread_mutex_unlock(&work->mutex);
    }
}

static struct thread_work *head, *tail;

void create_new_thread_area(struct thread_work **t)
{
    struct thread_work *new;
    static work;

    new = calloc(1, sizeof(*new));
    if (!new)
        return;

    work++;
    new->work = work;
    pthread_mutex_init(&new->mutex, NULL);
    pthread_cond_init(&new->cond, NULL);
    *t = new;

    if (!head) {
        head = new;
        tail = new;
    } else {
        tail->next = new;
        tail = new;
    }
}

int main(void)
{
    int n_thread = 7;
    pthread_t tid[n_thread];
    int ret;
    int i;

    for (i = 0; i < n_thread; i++) {
        struct thread_work *work;

        create_new_thread_area(&work);

        ret = pthread_create(&tid[i], NULL, thread_func, work);
    }

    while (1) {
        struct thread_work *work;

        for (work = head; work; work = work->next) {
            pthread_mutex_lock(&work->mutex);
            printf("waking up thread work %d\n", work->work);
            pthread_cond_signal(&work->cond);
            pthread_mutex_unlock(&work->mutex);
        }
        sleep(1);
    }

    return 0;
}

