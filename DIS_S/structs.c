/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 16:08:04 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/07 16:17:18 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dis.h"

t_operation	*new_operation(int op_code)
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
