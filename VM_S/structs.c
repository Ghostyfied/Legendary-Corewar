#include "vm.h"

t_operation *new_operation(int op_code)
{
	t_operation *new;

	new = MEM(t_operation);
	new->op_code = op_code;
	return (new);
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
