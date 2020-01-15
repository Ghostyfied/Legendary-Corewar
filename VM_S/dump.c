/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 11:27:18 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/15 17:27:17 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			dump(t_byte *arena, int line, int *idx)
{
	int		j;
	char	*hex;

	j = 0;
	hex = get_hex(line, 2);
	ft_printf("0x%s : ", hex);
	free(hex);
	while (j < 64)
	{
		hex = get_hex(arena[*idx], 1);
		ft_printf("%s ", hex);
		free(hex);
		(*idx)++;
		j++;
	}
	ft_putendl("");
}

void				dump64(t_vm *vm)
{
	int		i;
	int		idx;
	int		line;

	i = 0;
	line = 0;
	idx = 0;
	while (i < 64)
	{
		dump(ARENA, line, &idx);
		line += 64;
		i++;
	}
	free_vm(vm);
	exit(0);
}
