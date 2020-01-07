#include "vm.h"

t_cursor	*new_cursor(int	position, int r1, long id)
{
	t_cursor *c;

	c = MEM(t_cursor);
	c->id = id;
	c->position = position;
	c->registry[0] = r1;
	c->moved = true;
	return (c);
}

void		add_cursor(t_cursor **head, t_cursor *new)
{
	if (!head)
		return ;
	new->next = *head;
	*head = new;
}

t_cursor	*copy_cursor(t_cursor *src, int position, long id)
{
	t_cursor *cpy;

	cpy = MEM(t_cursor);
	ft_memcpy(cpy, src, sizeof(t_cursor));
	cpy->position = position;
	cpy->id = id;
	return (cpy);
}

t_cursor	*delete_cursor(t_cursor *head, long cursor_id)
{
	t_cursor *ret;

	if (!head)
		return (head);
	if (head->id == cursor_id)
	{
		ret = head->next;
		free(head);
		return (ret);
	}
	head->next = delete_cursor(head->next, cursor_id);
	return (head);
}
