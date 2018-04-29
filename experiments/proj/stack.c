#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct __stack {
	void *data;
	struct __stack *next;
} stack;

void Push(stack **head, void *item)
{
	stack *temp;

	if (*head == 0) {
		return;
	}

	temp = calloc(1, sizeof(stack));
	temp->data = item;

	temp->next = *head;
	*head = temp;
}

void print_stack(stack **head)
{
	stack *t;

	t = *head;
	while (t) {
		printf("%p\n", t);
		t = t->next;
	}
}
void * Pop(stack **head)
{
	stack *temp;

	if (*head == 0) {
		return 0;
	}
	temp = *head;

	*head = (*head)->next;
	return temp;
}

main()
{
	stack *t;
	stack *stack;

	stack = calloc(1, sizeof(stack));

	int count = 1230;
	int c = 1230;

	while (count--) {
		void *data;
		data = calloc(1, sizeof(1));
		Push(&stack, data);
	}

	while (c-- >= 0) {
		t = Pop(&stack);
		printf("- %p\n", t);
		free(t->data);
		free(t);
	}
}

