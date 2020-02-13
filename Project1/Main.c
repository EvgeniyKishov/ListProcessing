#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

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
* памяти.
*/
void kfree(void **p)
{
	free(*p);
	*p = NULL;
}

struct node {
	int id;
	double x, y;
};

struct list {
	void *data;
	struct list *next;
};

void add_list_item(void *data, struct list **head)
{
	struct list *new_head = kcalloc(1, sizeof(struct list));
	new_head->data = data;
	new_head->next = *head;
	*head = new_head;
}

void free_list_item(struct list **l)
{
	kfree(&(*l)->data);
	(*l)->next = NULL;
	kfree(l);
};

void remove_list_item(struct list *prev_item, struct list **del_item)
{
	struct list *tmp = NULL;
	//если удаляется вершина списка - переприсвоить её
	//...это же условие обрабатывает случай одного оставшегос¤ узла
	if (prev_item == NULL) {
		tmp = (*del_item)->next;
		free_list_item(del_item);
		*del_item = tmp;
	} else {
		// "перекидываем" связь через удаляемый узел
		prev_item->next = (*del_item)->next;
		free_list_item(del_item);
	}
}

struct list *find_item_by_id(struct list **prev, struct list *head, void *id)
{
	*prev = NULL;
	while (head != NULL) {
		if ( *(int*)head->data == *(int*)id ) 
			return head;
		*prev = head;
		head = head->next;
	}
	return NULL;
}

int delete_list_item(struct list **head, void *find_data,
	struct list *(*find)(struct list **, struct list *, void *))
{
	struct list *del_item = NULL;
	struct list *prev_item = NULL;

	del_item = find(&prev_item, *head, find_data);
	if (del_item == NULL)
		return -1;
	if (del_item == *head)
		remove_list_item(prev_item, head);
	else
		remove_list_item(prev_item, &del_item);
	return 0;
}

int main()
{
	struct list *nlist = NULL;

	struct node *new_node = kcalloc(1, sizeof(struct node));
	new_node->id = 1;
	new_node->x = 3.4;
	new_node->y = 2.3;

	add_list_item(new_node, &nlist);

	new_node = kcalloc(1, sizeof(struct node));
	new_node->id = 2;
	new_node->x = 5.6;
	new_node->y = 1.5;

	add_list_item(new_node, &nlist);

	int id = 1;
	delete_list_item(&nlist, &id, find_item_by_id);

	printf("Hello world!\n");
	return 0;
}
