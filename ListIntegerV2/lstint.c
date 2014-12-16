#include "lstint.h"

void lstint_increment_counter(list l)
{
	(*l)->counter++;
}

void lstint_decrement_counter(list l)
{
	(*l)->counter--;
}

element *lstint_first_element(list l)
{
	return (*l)->first;
}

element *lstint_last_element(list l)
{
	return (*l)->last;
}

void lstint_free_recursive(element *element)
{
	if (element->previous)
	{
		lstint_free_recursive(element->previous);
	}

	free(element);
}

int lstint_get_value_at_index_recursive(element *element, int index)
{
	if (!index)
	{
		return element->value;
	}
	else
	{
		return lstint_get_value_at_index_recursive(element->next, --index);
	}
}

void lstint_remove_value_at_index_recursive(element *element, int index)
{
	if (!index)
	{
		element->previous->next = element->next;
		element->next->previous = element->previous;
		free(element);
	}
	else
	{
		lstint_remove_value_at_index_recursive(element->next, --index);
	}
}

element *lstint_create_new_element(int value)
{
	element *new_element = (element *)malloc(sizeof(element));
	new_element->previous = NULL;
	new_element->value = value;
	new_element->next = NULL;
	return new_element;
}

void lstint_append_first_element(list l, element *first_element)
{
	(*l)->first = first_element;
	(*l)->last = first_element;
}

list lstint_initialize_list()
{
	list l = (struct list_struct **)malloc(sizeof(struct list_struct *));
	(*l) = (struct list_struct *)malloc(sizeof(struct list_struct));
	(*l)->first = NULL;
	(*l)->last = NULL;
	(*l)->counter = 0;

	return l;
}

bool lstint_is_empty_list(list l)
{
	return !((*l)->first) ? true : false;
}

void lstint_append_top(list l, int value)
{
	element *new_element = lstint_create_new_element(value);

	if (lstint_is_empty_list(l))
	{
		lstint_append_first_element(l, new_element);
	}
	else
	{
		((*l)->first)->previous = new_element;
		new_element->next = (*l)->first;
		(*l)->first = new_element;
	}

	lstint_increment_counter(l);
}

void lstint_append_bottom(list l, int value)
{
	element *new_element = lstint_create_new_element(value);

	if (lstint_is_empty_list(l))
	{
		lstint_append_first_element(l, new_element);
	}
	else
	{
		new_element->previous = (*l)->last;
		((*l)->last)->next = new_element;
		(*l)->last = new_element;
	}

	lstint_increment_counter(l);
}

int lstint_count(list l)
{
	return (*l)->counter;
}

int lstint_get_value_at_index(list l, int index)
{
	if (index >= 0 && index < lstint_count(l))
	{
		return lstint_get_value_at_index_recursive(lstint_first_element(l), index);
	}
	else
	{
		return -1;
	}
}

void lstint_remove_value_at_index(list l, int index)
{
	if (index >= 0 && index < lstint_count(l))
	{
		if (index == 0)
		{
			element *first_element = lstint_first_element(l);
			(((*l)->first)->next)->previous = NULL;
			(*l)->first = ((*l)->first)->next;
			free(first_element);
		}
		else if (index == (lstint_count(l) - 1))
		{
			element *last_element = lstint_last_element(l);
			(((*l)->last)->previous)->next = NULL;
			(*l)->last = ((*l)->last)->previous;
			free(last_element);
		}
		else
		{
			lstint_remove_value_at_index_recursive(lstint_first_element(l), index);
		}

		lstint_decrement_counter(l);
	}
}

size_t lstint_size(list l)
{
	return sizeof(list) + sizeof(struct list_struct) + (sizeof(element) * lstint_count(l));
}

void lstint_free(list l)
{
	lstint_free_recursive(lstint_last_element(l));
	free((*l));
}
