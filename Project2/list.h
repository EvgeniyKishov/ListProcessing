#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include "mm.h"

typedef struct list {
	void *data;
	bool is_data_alloc;
	struct list *next;
}list_t;

void add_list_item(void *data, list_t **head, bool is_data_alloc);
int delete_list_item(list_t **head, void *find_data,
		     list_t *(*find)(list_t **, list_t *, void *),
		     void (*free_data)(void *data));
void pop_list(list_t **head, void (*free_data)(void *data));

#endif 