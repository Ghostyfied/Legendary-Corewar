/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 11:27:18 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/10 15:54:01 by rvan-ket      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				dump64(t_vm *vm)
{
	int	i;
	int	j;
	int	idx;
	int	line;

	i = 0;
	line = 0;
	idx = 0;
	while (i < 64)
	{
		j = 0;
		ft_printf("0x%s : ", get_hex(line, 2));
		while (j < 64)
		{
			ft_printf("%s ", get_hex(ARENA[idx], 1));
			idx++;
			j++;
		}
		ft_putendl("");
		line += 64;
		i++;
	}
	// free_vm(vm);
	exit(0);
}

void				dump32(t_vm *vm)
{
	int i;
	int j;
	int idx;
	int	line;

	i = 0;
	line = 0;
	idx = 0;
	while (i < 128)
	{
		j = 0;
		ft_printf("0x%s : ", get_hex(line, 2));
		while (j < 32)
		{
			ft_printf("%s ", get_hex(ARENA[idx], 1));
			idx++;
			j++;
		}
		ft_putendl("");
		line += 32;
		i++;
	}
	free_vm(vm);
	exit(0);
}
