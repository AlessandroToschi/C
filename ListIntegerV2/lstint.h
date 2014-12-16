#include <stdlib.h>
#include <stdbool.h>

typedef struct element
{
	struct element *previous;
	int value;
	struct element *next;
}element;

struct list_struct
{
	element *first;
	element *last;
	int counter;
};

typedef struct list_struct ** list;

extern list lstint_initialize_list();
extern bool lstint_is_empty_list(list l);
extern void lstint_append_top(list l, int value);
extern void lstint_append_bottom(list l, int value);
extern int lstint_count(list l);
extern int lstint_get_value_at_index(list l, int index);
extern void lstint_remove_value_at_index(list l, int index);
extern size_t lstint_size(list l);
extern void lstint_free(list l);
