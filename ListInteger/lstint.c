#include "lstint.h"

element *lstint_create_new_element(int value)
{
	element *new_element = (element *)malloc(sizeof(element));
	new_element->value = value;
	new_element->next = NULL;
	return new_element;
}

bool lstint_empty_list(list l)
{
	return !(*l) ? true : false;
}

list lstint_initialize_list()
{
	list new_list = (element **)malloc(sizeof(element *));
	*new_list = NULL;
	return new_list;
}

void lstint_append_value(list l, int value)
{
	element *new_element = lstint_create_new_element(value);

	if (lstint_empty_list(l))
	{
		*l = new_element;
	}
	else
	{
		element *pointer = *l;
		for (; pointer->next; pointer = pointer->next);
		pointer->next = new_element;
	}
}

int	lstint_count(list l)
{
	if (lstint_empty_list(l))
	{
		return 0;
	}
	else
	{
		int count = 1;
		element *pointer = *l;
		for (; pointer->next; count++, pointer = pointer->next);
		return count;
	}
}

int lstint_first_value(list l)
{
	return lstint_empty_list(l) ? -1 : (*l)->value;
}

int lstint_last_value(list l)
{
	if (lstint_empty_list(l))
	{
		return -1;
	}
	else
	{
		element *pointer = *l;
		for (; pointer->next; pointer = pointer->next);
		return pointer->value;
	}
}

int	lstint_get_value_at_index(list l, int index)
{
	if (lstint_empty_list(l) || index < 0 || index >= lstint_count(l))
	{
		return -1;
	}
	else
	{
		element *pointer = *l;
		for (int i = 0; i < index; i++, pointer = pointer->next);
		return pointer->value;
	}
}

void lstint_remove_value_at_index(list l, int index)
{
	if (!lstint_empty_list(l) && index >= 0 && index < lstint_count(l))
	{
		if (index == 0)
		{
			element *pointer = *l;
			*l = pointer->next;
			free(pointer);
		}
		else if (index == (lstint_count(l) - 1))
		{
			element *pointer = *l;
			for (int i = 0; i < index - 1; i++, pointer = pointer->next);
			element *next_pointer = pointer->next;
			free(next_pointer);
			pointer->next = NULL;
		}
		else
		{
			element *pointer = *l;
			for (int i = 0; i < index - 1; i++, pointer = pointer->next);
			element *next_pointer = pointer->next;
			pointer->next = next_pointer->next;
			free(next_pointer);
		}
	}
}
