/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 11:27:18 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/08 11:35:34 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char			*get_hex(unsigned int nb, int bytesize)
{
	char *hex;

	bytesize *= 2;
	hex = ft_strnew(bytesize);
	bytesize--;
	while (bytesize >= 0)
	{
		hex[bytesize] = "0123456789abcdef"[nb % 16];
		nb /= 16;
		bytesize--;
	}
	return (hex);
}

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
	free_vm(vm);
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
