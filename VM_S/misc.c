/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 14:35:54 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/10 14:42:45 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			valid_opcode(t_byte opcode)
{
	if (opcode < 1 || opcode > 16)
		return (0);
	return (1);
}

int			get_bytes(t_byte *arena, int idx, int amount)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	while (i < amount)
	{
		value <<= 8;
		value = value | arena[get_arena_index(idx, i)];
		i++;
	}
	if (amount == 2)
		return ((short)value);
	return (value);
}

/*
** Returns the correct index of the amount of moved bytes in the arena
*/

int			get_arena_index(int current, int move)
{
	if (move >= 0)
		return ((current + move) % MEM_SIZE);
	current += move;
	if (current < 0)
		return ((MEM_SIZE - 1) + current);
	return (current);
}

void			put_value(t_byte *arena, int idx, void *value)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		arena[get_arena_index(idx, i)] = ((t_byte*)value)[i];
		i++;
	}
}
