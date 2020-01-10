/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 16:00:30 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/10 14:43:47 by awehlbur      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_champions(t_champ *champs, int champ_nb)
{
	int i;

	i = 0;
	while (i < champ_nb)
	{
		ft_printf("%d\n", champs[i].id);
		ft_printf("%-10s : %s\n", ".name", champs[i].name);
		ft_printf("%-10s : %s\n", ".comment", champs[i].comment);
		ft_printf("%-10s : %d\n", "code_size", champs[i].code_size);
		ft_printf("%-10s : %d\n", "start_pos", champs[i].starting_pos);
		ft_putendl("");
		i++;
	}
}

void	print_byte(const void *byte, size_t size)
{
	int					idx;
	size_t				i;
	const unsigned char	*b;

	i = 0;
	b = (const unsigned char *)byte;
	while (i < size)
	{
		idx = 7;
		while (idx >= 0)
		{
			if (idx == 3)
				write(1, " ", 1);
			if ((b[i] & (1 << idx)) != 0)
				write(1, "1", 1);
			else
				write(1, "0", 1);
			idx--;
		}
		ft_putendl("");
		i++;
	}
}

void	print_cursor(t_cursor *cursor, int reg)
{
	int i;

	i = 0;
	ft_printf("%-8s : %d\n", "id", cursor->id);
	ft_printf("%-8s : %d\n", "position", cursor->position);
	ft_printf("%-8s : %d\n", "opcode", cursor->opcode);
	ft_printf("%-8s : %d\n", "wait_cy", cursor->wait_cycles);
	if (reg == false)
	{
		ft_putendl("");
		return ;
	}
	while (i < REG_NUMBER)
	{
		ft_printf(" r%-2d : %d\n", i, cursor->registry[i]);
		i++;
	}
	ft_putendl("");
}

void	print_cursors(t_cursor *cursors, int reg)
{
	if (!cursors)
		return ;
	print_cursor(cursors, reg);
	print_cursors(cursors->next, reg);
}

void	print_arg(t_arg *args, int nb_arg)
{
	int		i;
	char	*type;

	i = 0;
	while (i < nb_arg)
	{
		type = args[i].type == \
			T_REG ? "T_REG" : (args[i].type == T_DIR ? "T_DIR" : "T_IND");
		ft_printf("arg:%d %s, size %d, value : %d\n", i, \
			type, args[i].size, args[i].value);
		i++;
	}
	ft_putendl("");
}
