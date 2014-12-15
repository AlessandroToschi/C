#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
	int value;
	struct element *next;
}element;

typedef element** list;

extern list lstint_initialize_list();
extern bool lstint_empty_list(list l);
extern void lstint_append_value(list l, int value);
extern int	lstint_count(list l);
extern int	lstint_first_value(list l);
extern int	lstint_last_value(list l);
extern int	lstint_get_value_at_index(list l, int index);
extern void lstint_remove_values(list l, int value);
extern void lstint_remove_value_at_index(list l, int index);
extern void lstint_free(list l);
