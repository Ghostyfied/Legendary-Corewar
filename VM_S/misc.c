/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 14:35:54 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/07 14:36:44 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			octal_valid(t_byte octal, int nb_arg)
{
	int shift;

	if (octal & 3)
		return (0);
	if (nb_arg == 3)
		return (1);
	shift = nb_arg * 2;
	if (((octal << shift) & 0xff))
		return (0);
	return (1);
}

int			valid_opcode(t_byte opcode)
{
	if (opcode < 1 || opcode > 16)
		return (0);
	return (1);
}

int			get_2bytes(t_byte *arena)
{
	short b;

	ft_memcpy(&b, arena, 2);
	return (swap_16(b));
}

int			get_4bytes(t_byte *arena)
{
	int b;

	ft_memcpy(&b, arena, 4);
	return (swap_32(b));
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
