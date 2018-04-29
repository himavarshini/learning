#include <stdio.h>
#include <stdlib.h>

struct dll {
	int data;
	struct dll *prev;
	struct dll *next;
};

static struct dll *head, *tail;

int Add(int d)
{
	struct dll *new;

	new = calloc(1, sizeof(*new));
	if (!new) {
		return 0;
	}

	new->data = d;

	if (!head) {
		head = new;
		tail = new;
	} else {
		new->prev = tail;
		tail->next = new;
		tail = new;
	}

	return 1;
}