#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include "list.h"
#include "mm.h"

typedef struct node {
	int id;
	double *r;
}node_t;

void free_node_data(node_t *node)
{
	node->id = 0;
	kfree(&node->r);
}

list_t *lfind_double(list_t **prev, list_t *head, void *val)
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

list_t *find_item_by_id(list_t **prev, list_t *head, void *id)
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
	list_t *dlist = NULL;
	
	//double *a = kcalloc(1, sizeof(double));
	//*a = 2.5;
	//double a = 2.5;
	node_t *node1 = kcalloc(1, sizeof(node_t));
	node1->id = 1;
	node1->r = kcalloc(2, sizeof(double));
	node1->r[0] = 1.2; node1->r[1] = 1.5;
	add_list_item(node1, &dlist, true);

	//double *b = kcalloc(1, sizeof(double));
	//*b = 3.1;
	//double b = 3.1;
	node_t node2 = { .id = 2, .r = NULL };
	node2.r = kcalloc(2, sizeof(double));
	node2.r[0] = 2.3; node2.r[1] = 2.5;
	add_list_item(&node2, &dlist, false);

	//double c = 2.5;
	int id = 1;
	delete_list_item(&dlist, &id, find_item_by_id, free_node_data);

	printf("Hello world!\n");
	return 0;
}
