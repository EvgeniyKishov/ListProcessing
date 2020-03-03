#include <stdlib.h>

struct node {
	int id;
	double *r;
};

void free_node_data(struct node *node)
{
	node->id = 0;
	free(node->r);
}

int main()
{
	struct node *n = calloc(1, sizeof(struct node));

	if (n != NULL) {
		n->id = 3;
		n->r = calloc(2, sizeof(double));
	}
	free_node_data(n);
}