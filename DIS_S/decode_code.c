/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   decode_code.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 16:07:47 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/17 15:33:58 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dis.h"

static int		get_dir(int fd, int op_code, int *type)
{
	short	b2;
	int		b4;

	*type = T_DIR;
	if (g_op_tab[op_code].dir_size == 2)
	{
		read(fd, &b2, 2);
		return (swap_16(b2));
	}
	else
	{
		read(fd, &b4, 4);
		return (swap_32(b4));
	}
}

static int		get_arg(int fd, t_byte octal, int op_code, int *type)
{
	t_byte	b1;
	short	b2;

	if ((octal & 3) == REG)
	{
		*type = T_REG;
		read(fd, &b1, 1);
		return (b1);
	}
	else if ((octal & 3) == DIR)
		return (get_dir(fd, op_code, type));
	else if ((octal & 3) == IND)
	{
		*type = T_IND;
		read(fd, &b2, 2);
		return (swap_16(b2));
	}
	ft_error("Argument error");
	return (-1);
}

static t_arg	*get_args(int fd, int op_code, t_byte octal, int *nb_arg)
{
	t_arg	*args;
	int		i;
	int		shift;

	*nb_arg = g_op_tab[op_code].nb_arg;
	if (!octal_valid(octal, *nb_arg))
		ft_error("Octal error");
	args = (t_arg*)ft_memalloc(sizeof(t_arg) * *nb_arg);
	i = 0;
	shift = 6;
	while (i < *nb_arg)
	{
		args[i].value = get_arg(fd, octal >> shift, op_code, &args[i].type);
		shift -= 2;
		i++;
	}
	return (args);
}

static void		dir_code(t_operation *op, t_byte op_code, int fd)
{
	short		b2;
	int			b4;

	op->args = MEM(t_arg);
	op->nb_arg = 1;
	op->args->type = T_DIR;
	if (g_op_tab[op_code].dir_size == 2)
	{
		read(fd, &b2, 2);
		op->args->value = swap_16(b2);
	}
	else
	{
		read(fd, &b4, 4);
		op->args->value = swap_32(b4);
	}
}

void			decode_code(int fd, t_champ *champ)
{
	t_byte		op_code;
	t_byte		octal;
	t_operation *op;

	while (read(fd, &op_code, 1))
	{
		op = new_operation(op_code);
		if (g_op_tab[op_code].octal)
		{
			read(fd, &octal, 1);
			op->args = get_args(fd, op_code, octal, &op->nb_arg);
		}
		else
			dir_code(op, op_code, fd);
		add_operation(&champ->operations, op);
	}
}
