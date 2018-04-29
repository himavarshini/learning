#include <stdio.h>

struct queue {
	int data;
	struct queue *next;
};

struct queue *front, *rear;

int queue_enter(int val)
{
	struct queue *new;

	new = calloc(1, sizeof(struct queue));
	if (!new) {
		return -1;
	}

	new->data = val;

	if (!front) {
		front = new;
		rear = new;
	} else {
		rear->next = new;
		rear = new;
	}

	return 0;
}

int queue_delete()
{
	struct queue *next;
	int data;

	next = front;
	if (front == NULL) {
		return -1;
	}

	front = front->next;
	data = next->data;
	free(next);

	return data;
}

int main(void)
{
	int n_elems = 5;
	int e1 = 10, e2 = 1, e3 = 4, e4 = 8, e5 = 6;

	queue_enter(e1);
	queue_enter(e2);
	queue_enter(e3);
	queue_enter(e4);
	queue_enter(e5);

	printf("item in the queue -> popped %d\n", queue_delete());
	printf("item in the queue -> popped %d\n", queue_delete());
	printf("item in the queue -> popped %d\n", queue_delete());
	printf("item in the queue -> popped %d\n", queue_delete());
	printf("item in the queue -> popped %d\n", queue_delete());
	printf("item in the queue -> popped %d\n", queue_delete());

	return 0;
}

