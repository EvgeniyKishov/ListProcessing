#include "list.h"

static void free_list_item(struct list **l, void (*free_data)(void *data))
{
	if (free_data != NULL)
		free_data((*l)->data);
	if ((*l)->is_data_alloc)
		kfree(&(*l)->data);
	else
		(*l)->data = NULL;

	(*l)->next = NULL;
	kfree(l);
}

static void remove_list_item(struct list *prev_item, struct list **del_item,
			     void (*free_data)(void *data))
{
	struct list *tmp = NULL;
	/*
	* Если удаляется вершина списка - переприсвоить её.
	* Это же условие обрабатывает случай одного оставшегося узла.
	*/
	if (prev_item == NULL) {
		tmp = (*del_item)->next;
		free_list_item(del_item, free_data);
		*del_item = tmp;
	} else {
		/* "перекидываем" связь через удаляемый узел */
		prev_item->next = (*del_item)->next;
		free_list_item(del_item, free_data);
	}
}

void push_list(void *data, struct list **head, bool is_data_alloc)
{
	struct list *new_head = kcalloc(1, sizeof(struct list));
	new_head->data = data;
	new_head->is_data_alloc = is_data_alloc;
	new_head->next = *head;
	*head = new_head;
}

int delete_list_item(struct list **head, void *find_data,
		struct list *(*find)(struct list **, struct list *, void *),
		void (*free_data)(void *data))
{
	struct list *del_item = NULL;
	struct list *prev_item = NULL;

	del_item = find(&prev_item, *head, find_data);
	if (del_item == NULL)
		return -1;
	if (del_item == *head)
		remove_list_item(prev_item, head, free_data);
	else
		remove_list_item(prev_item, &del_item, free_data);
	return 0;
}

void pop_list(struct list **head, void (*free_data)(void *data))
{
	remove_list_item(NULL, head, free_data);
}

void delete_list(struct list **head, void (*free_data)(void *data))
{
	while (*head != NULL) {
		pop_list(head, free_data);
	}
}