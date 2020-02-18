#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include "list.h"
#include "mm.h"

struct node {
	int id;
	double *r;
};

void free_node_data(struct node *node)
{
	node->id = 0;
	kfree(&node->r);
}

struct list *lfind_double(struct list **prev, struct list *head, void *val)
{
	*prev = NULL;
	while (head != NULL) {
		if (*(double *)head->data == *(double *)val)
			return head;
		*prev = head;
		head = head->next;
	}
	return NULL;
}

struct list *find_item_by_id(struct list **prev, struct list *head, void *id)
{
	*prev = NULL;
	while (head != NULL) {
		if (*(int *)head->data == *(int *)id)
			return head;
		*prev = head;
		head = head->next;
	}
	return NULL;
}

int main()
{
	struct list *dlist = NULL;
	
	//double *a = kcalloc(1, sizeof(double));
	//*a = 2.5;
	//double a = 2.5;
	struct node *node1 = kcalloc(1, sizeof(struct node));
	node1->id = 1;
	node1->r = kcalloc(2, sizeof(double));
	node1->r[0] = 1.2; node1->r[1] = 1.5;
	push_list(node1, &dlist, true);

	//double *b = kcalloc(1, sizeof(double));
	//*b = 3.1;
	//double b = 3.1;
	struct node node2 = { .id = 2, .r = NULL };
	node2.r = kcalloc(2, sizeof(double));
	node2.r[0] = 2.3; node2.r[1] = 2.5;
	push_list(&node2, &dlist, false);

	//double c = 2.5;
	int id = 1;
	delete_list_item(&dlist, &id, find_item_by_id, free_node_data);
	//pop_list(&dlist, free_node_data);

	printf("Hello world!\n");
	return 0;
}
