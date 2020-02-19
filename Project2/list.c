#include "list.h"

static void free_list_item(list_t **l, void (*free_data)(void *data))
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

static void remove_list_item(list_t *prev_item, list_t **del_item,
	void (*free_data)(void *data))
{
	list_t *tmp = NULL;
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

void push_list(void *data, list_t **head, bool is_data_alloc)
{
	list_t *new_head = kcalloc(1, sizeof(struct list));
	new_head->data = data;
	new_head->is_data_alloc = is_data_alloc;
	new_head->next = *head;
	*head = new_head;
}

int delete_list_item(list_t **head, void *find_data,
		     list_t *(*find)(list_t **, list_t *, void *),
		     void (*free_data)(void *data))
{
	list_t *del_item = NULL;
	list_t *prev_item = NULL;

	del_item = find(&prev_item, *head, find_data);
	if (del_item == NULL)
		return -1;
	if (del_item == *head)
		remove_list_item(prev_item, head, free_data);
	else
		remove_list_item(prev_item, &del_item, free_data);
	return 0;
}

void pop_list(list_t **head, void (*free_data)(void *data))
{
	remove_list_item(NULL, head, free_data);
}