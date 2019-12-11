/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arg.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 13:03:16 by fhignett       #+#    #+#                */
/*   Updated: 2019/12/11 13:05:41 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Checks all args to get the type.
** Size is the number of arguments teh operation is supposed to have.
*/

void		get_arg_type(t_operation **op, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if ((*op)->arg[i].op[0] == DIRECT_CHAR)
			(*op)->arg[i].arg = T_DIR;
		else if ((*op)->arg[i].op[0] == 'r')
			(*op)->arg[i].arg = T_REG;
		else
			(*op)->arg[i].arg = T_IND;
		i++;
	}
}

/*
** Returns hex string for each argument.
*/

static char	*get_arg(t_operation *head, t_arg arg, t_operation *op, int *size)
{
	char	*s;
	int		value;
	char	*lbl;

	s = NULL;
	if (!arg.arg)
		return (s);
	value = ft_atoi(&arg.op[1]);
	if (arg.arg == T_REG)
		return (get_hex(value, 1));
	lbl = ft_strchr(arg.op, LABEL_CHAR);
	if (lbl)
		value = find_label(head, lbl + 1, op->size_index, size);
	else if (arg.arg == T_IND)
		value = ft_atoi(arg.op);
	if (arg.arg == T_IND)
		s = get_hex(value, 2);
	else if (arg.arg == T_DIR)
		s = get_hex(value, g_op_tab[op->op].dir_size);
	return (s);
}

static int	check_arg(t_arg arg)
{
	int i;
	int end;

	i = arg.arg == T_IND ? 0 : 1;
	if (arg.op[i] == LABEL_CHAR)
		return (1);
	end = chr_idx(arg.op, ' ');
	end = !end ? ft_strlen(arg.op) : end - 1;
	if (i == end)
		return (0);
	while (i < end)
	{
		if (!ft_isdigit(arg.op[i]))
			return (0);
		i++;
	}
	if (arg.op[end] && arg.op[end + 1] != COMMENT_CHAR)
		return (0);
	return (1);
}

void		arg_exc_code(t_operation *tmp, t_operation *head, int *size_array)
{
	int		i;
	char	*args;

	i = 0;
	while (i < 3)
	{
		if (tmp->arg[i].op && !check_arg(tmp->arg[i]))
		{
			ft_putendl(tmp->arg[i].op);
			ft_error("Argument error");
		}
		args = get_arg(head, tmp->arg[i], tmp, size_array);
		if (args)
			tmp->executable = ft_strjoinfree(tmp->executable, args);
		i++;
	}
}
