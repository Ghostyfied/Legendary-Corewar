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
	new->next = *head;
	*head = new;
}

t_operation	*new_operation(t_label *labels)
{
	t_operation *op;

	op = MEM(t_operation);
	op->labels = labels;
	return (op);
}
