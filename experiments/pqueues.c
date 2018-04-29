struct pqueue {
	int prio;
	void *data;
	struct pqueue *next;
};

int add(struct pqueue **head, int prio)
{
	struct pqueue *new;

	new = calloc(1, sizeof(struct pqueue));
	if (new == 0) {
		return 1;
	}

	new->prio = prio;

	if (!*head) {
		*head = new;
		return 0;
	}

	struct pqueue *p;
	struct pqueue *p1;

	p = p1 = *head;

	while (p) {
		if (prio >= p->prio) {
			if (p == *head) {
				*head = new;
				(*head)->next = p;
				return 0;
			} else {
				p1->next = new;
				new->next = p;
				return  0;
			}
		}
		p1 = p;
		p = p->next;
	}

	return 0;
}

int remove(struct pqueue **head, int prio)
{
	struct pqueue *p1;
	struct pqueue *p;

	p = p1 = *head;

	while (p) {
		if (prio == p->prio) {
			if (p == *head) {
				*head = p->next;
				free(p);
				return 1;
			} else {
				p1->next = p->next;
				free(p);
				return 1;
			}
		}
		p1 = p;
		p = p->next;
	}

}

struct pqueue * peek_prio(struct pqueue **head)
{
	struct pqueue *p;

	p = *head;
	return p;
}

int wrap_around(struct pqueue **head, struct pqueue *elm)
{
	struct pqueue *p1;
	struct pqueue *p;

	p = p1 = *head;

	while (p) {
		if (p == elm) {
			if (p == *head) {
				*head = p->next;
				free(p);
				return 1;
			} else {
				p1->next = p->next;
				free(p);
				return 1;
			}
		}
		p1 = p;
		p = p->next;
	}
}

main()
{
	struct pqueue *head = 0;
	struct pqueue *peek;

	add(&head, 1);
	add(&head, 2);
	add(&head, 45);
	add(&head, 3);
	add(&head, 482);
	add(&head, 42423);
	add(&head, 3113);

peek_data:
	peek = peek_prio(&head);
	if (peek) {
		printf("prio %d\n", peek->prio);
		wrap_around(&head, peek);
		goto peek_data;
	}
}
