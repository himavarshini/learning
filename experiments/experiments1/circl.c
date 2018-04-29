#include <stdio.h>

struct list_circle *head, *last;

struct list_circle {
	int data;
	struct list_circle *next;
	struct list_circle *head;
	struct list_circle *last;
};


int
list_circle_add(struct list_circle **head, int data)
{

	struct list_circle *elem;
	struct list_circle *elem1;

	elem = *head;

	elem1 = calloc(1, sizeof(struct list_circle));
	if (!elem1) {
		return -1;
	}

	elem1->data = data;

	if (!elem) {
		*head = elem1;
		elem1->next = *head;
		last = elem1;
	} else {
		while (elem->next != *head)
			elem = elem->next;

		elem->next = elem1;
		elem1->next = *head;
		last = elem1;
	}

	return 0;
}

int
list_circle_insert_tail(struct list_circle **head, int data)
{
	struct list_circle *elem;
	struct list_circle *new;
	struct list_circle *elem1;

	elem = *head;

	if (!elem) {
		new = calloc(1, sizeof(struct list_circle));
		if (!new)
			return -1;
		new->data = data;
		*head=  new;

		new->next = *head;
		last = new;
		return 0;
	}

	elem1 = elem;
	do {
		if (elem->data >= data) {
			new = calloc(1, sizeof(struct list_circle));
			if (!new) {
				return -1;
			}
			new->data = data;
			elem1->next = new;
			new->next = elem;
			return 0;
		}
		elem1 = elem;
		elem = elem->next;
	} while (elem != *head);

	new = calloc(1, sizeof(struct list_circle));
	new->data = data;
	last->next = new;
	last = new;
	new->next = *head;

	return 0;
}

int
list_circle_delete(struct list_circle **head, int data)
{
	struct list_circle *elem;
	struct list_circle *elem1;

	elem = *head;

	if (elem->data == data) {
		elem1 = *head;
		(*head) = elem->next;
		last->next = (*head);
		free(elem1);
	} else {
		elem1 = elem;
		do {
			if (elem->data == data) {
				elem1->next = elem->next;
				free(elem);
				return 0;
			}
			elem1 = elem;
			elem = elem->next;
		} while (elem != *head);
	}

	return -1;
}
		
int
list_circle_disp(struct list_circle **head)
{
	struct list_circle *elem;

	elem = *head;
	int count = 0;

	do {
		count++;
		printf("%p %d %d\n", elem, elem->data, count);
		elem = elem->next;
	} while (elem != *head);

}

main()
{
	int elems = 10;
	struct list_circle *head = 0;

	list_circle_insert_tail(&head, 2);
	list_circle_insert_tail(&head, 5);
	list_circle_insert_tail(&head, 1);
	list_circle_insert_tail(&head, 3);
	list_circle_insert_tail(&head, 6);
	list_circle_insert_tail(&head, 7);
	list_circle_insert_tail(&head, 4);
	list_circle_insert_tail(&head, 8);
	list_circle_insert_tail(&head, 9);
	//list_circle_delete(&head, 4);
	//list_circle_delete(&head, 1);
	list_circle_insert_tail(&head, 10);

	//list_circle_delete(&head, 10);

	list_circle_disp(&head);

	return 0;
}
