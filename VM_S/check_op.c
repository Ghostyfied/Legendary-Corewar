/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_op.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 15:20:46 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/10 13:18:58 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Gets size of octal
*/

static int		get_size(t_byte opcode, t_byte octal, int nb_arg)
{
	int shift;
	int i;
	int size;

	shift = 6;
	i = 0;
	size = 0;
	while (i < nb_arg)
	{
		if (((octal >> shift) & 3) == REG)
			size += 1;
		else if (((octal >> shift) & 3) == DIR)
			size += g_op_tab[opcode].dir_size;
		else if (((octal >> shift) & 3) == IND)
			size += 2;
		i++;
		shift -= 2;
	}
	return (size);
}

static t_arg	get_arg(t_byte opcode, t_byte arg_type)
{
	t_arg arg;

	if ((arg_type & 3) == REG)
	{
		arg.size = 1;
		arg.type = T_REG;
		return (arg);
	}
	else if ((arg_type & 3) == DIR)
	{
		arg.size = g_op_tab[opcode].dir_size;
		arg.type = T_DIR;
		return (arg);
	}
	else
	{
		arg.size = 2;
		arg.type = T_IND;
		return (arg);
	}
}

/*
** op_idx = 2; Skips opcode and octal
*/

static t_arg	*get_args(t_cursor *c, t_byte octal, t_byte *arena)
{
	t_arg	*args;
	int		shift;
	int		i;
	int		op_idx;

	op_idx = 2;
	shift = 6;
	i = 0;
	args = (t_arg*)ft_memalloc(sizeof(t_arg) * g_op_tab[c->opcode].nb_arg);
	while (i < g_op_tab[c->opcode].nb_arg)
	{
		args[i] = get_arg(c->opcode, ((octal >> shift) & 3));
		args[i].value = get_bytes(arena, c->position + op_idx, args[i].size);
		shift -= 2;
		op_idx += args[i].size;
		i++;
	}
	return (args);
}

static void		check_octal_code(t_vm *vm, t_cursor *c)
{
	int		i;
	int		size;
	t_arg	*args;

	size = get_size(c->opcode, ARENA[c->position + 1],
					g_op_tab[c->opcode].nb_arg) + 2;
	if (!octal_valid(ARENA[c->position + 1], g_op_tab[c->opcode].nb_arg))
	{
		c->position += size;
		return ;
	}
	args = get_args(c, ARENA[c->position + 1], ARENA);
	i = 0;
	while (i < g_op_tab[c->opcode].nb_arg)
	{
		if ((args[i].type == T_REG && (args[i].value < 1 || args[i].value > 16))
			|| !(args[i].type & g_op_tab[c->opcode].args[i]))
		{
			free(args);
			c->position += size;
			return ;
		}
		i++;
	}
	do_op(vm, c, args, size);
}

/*
** Checks if operation/octal is valid that cursor has to execute
** and then calls do_op()
*/

void			execute_op(t_vm *vm, t_cursor *c)
{
	int		size;
	t_arg	*args;

	if (g_op_tab[c->opcode].octal)
		check_octal_code(vm, c);
	else
	{
		args = MEM(t_arg);
		size = 1 + g_op_tab[c->opcode].dir_size;
		args->size = g_op_tab[c->opcode].dir_size;
		args->value = get_bytes(ARENA, c->position + 1, args->size);
		args->type = T_DIR;
		do_op(vm, c, args, size);
	}
}
