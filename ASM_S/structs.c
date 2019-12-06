#include "asm.h"

t_label		*new_label(char *name)
{
	t_label *label;

	label = MEM(t_label);
	label->name = name;
	return (label);
}

void		add_label(t_label **head, t_label *new)
{
	if (!head)
		return ;
	new->next = *head;
	*head = new;
}

void		add_operation(t_operation **head, t_operation *new)
{
	if (!head)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	add_operation(&(*head)->next, new);
}

t_operation	*new_operation(t_label *labels)
{
	t_operation *op;
	static int	size_index;

	op = MEM(t_operation);
	op->labels = labels;
	op->size_index = size_index;
	size_index++;
	return (op);
}
