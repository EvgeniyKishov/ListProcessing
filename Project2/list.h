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

void push_list(void *data, struct list **head, bool is_data_alloc);
int delete_list_item(struct list **head, void *find_data,
		struct list *(*find)(struct list **, struct list *, void *),
		void (*free_data)(void *data));
void pop_list(struct list **head, void (*free_data)(void *data));
void delete_list(struct list **head, void (*free_data)(void *data));

#endif 