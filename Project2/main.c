#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

/**
* kcalloc() - выделение памяти и инициализация её нулями.
* @n: число объектов.
* @obj_size: размер одного объекта.
*
* Функция построена на основе стандартной функции calloc().
* Добавлена проверка на успешность выделения памяти.
*
* Возвращаемое значение: указатель на выделенную область памяти.
*/
void *kcalloc(size_t n, size_t obj_size)
{
	void *new_mem = NULL;
	new_mem = calloc(n, obj_size);

	if (!new_mem) {
		MessageBox(NULL, TEXT("Невозможно выделить память. \
					Выход из программы"),
			TEXT("Ошибка!"), MB_ICONERROR);
		exit(1);
	}

	return new_mem;
}

/**
* kfree() - освобождение памяти, выделенной функцией kcalloc().
* @p - указатель на указатель на область памяти.
*
* Функция построена на основе стандартной функции free(). Поведение kfree()
* отличается тем, что она дополнительно обнуляет указатель после освобождения  
* памяти./
*/
void kfree(void **p)
{
	free(*p);
	*p = NULL;
}

struct list {
	void *data;
	bool is_data_alloc;
	struct list *next;
};

struct node {
	int id;
	double *r;
};

void add_list_item(void *data, struct list **head, bool is_data_alloc)
{
	struct list *new_head = kcalloc(1, sizeof(struct list));
	new_head->data = data;
	new_head->is_data_alloc = is_data_alloc;
	new_head->next = *head;
	*head = new_head;
}

void free_node_data(struct node *node)
{
	node->id = 0;
	kfree(&node->r);
}

void free_list_item(struct list **l, void (*free_data)(void *data))
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

void remove_list_item(struct list *prev_item, struct list **del_item,
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
	add_list_item(node1, &dlist, true);

	//double *b = kcalloc(1, sizeof(double));
	//*b = 3.1;
	//double b = 3.1;
	struct node node2 = { .id = 2, .r = NULL };
	node2.r = kcalloc(2, sizeof(double));
	node2.r[0] = 2.3; node2.r[1] = 2.5;
	add_list_item(&node2, &dlist, false);

	//double c = 2.5;
	int id = 1;
	delete_list_item(&dlist, &id, find_item_by_id, free_node_data);

	printf("Hello world!\n");
	return 0;
}
