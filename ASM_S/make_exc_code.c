/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_exc_code.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 16:09:17 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/17 11:59:30 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Uses the int *size to add up the byte dist from
** the label name to the arg using the label.
** If label(index) is bigger then the arg(index) then step = -1.
** Add all the operation sizes until label(index) is the same as arg(index).
** Returns the amount of bytes from label to arg.
** Can be negative depending if label was called before or after arg.
*/

static int	calc_bytes_dist(int *size, int label, int arg)
{
	int i;
	int	step;
	int byte_dist;

	step = 1;
	byte_dist = 0;
	i = label;
	if (label > arg)
	{
		step = -1;
		byte_dist += size[arg];
		i--;
	}
	while (i != arg)
	{
		byte_dist += size[i];
		i += step;
	}
	byte_dist = step == -1 ? byte_dist : -byte_dist;
	return (byte_dist);
}

static int	eof_labels(t_label *eof_lbl, char *label, int size_idx, int *size)
{
	t_label *lbl;
	int		value;

	lbl = eof_lbl;
	value = 0;
	while (lbl)
	{
		if (ft_strequ(lbl->name, label))
		{
			while (size[size_idx])
			{
				value += size[size_idx];
				size_idx++;
			}
			return (value);
		}
		lbl = lbl->next;
	}
	return (0);
}

/*
** Finds and calculates the amount of bytes from
** arg:label to label:operation the cursor has to jump in the VM.
*/

int			find_label(t_operation *op, char *label, int size_idx, int *size)
{
	t_label		*lbl;
	int			value;

	value = eof_labels(op->eof_labels, label, size_idx, size);
	if (value)
		return (value);
	while (op)
	{
		lbl = op->labels;
		while (lbl)
		{
			if (ft_strequ(lbl->name, label))
				return (calc_bytes_dist(size, op->size_index, size_idx));
			lbl = lbl->next;
		}
		op = op->next;
	}
	ft_putendl(label);
	ft_error("Label doesn't exist");
	return (-1);
}

/*
** Gets all hex strings for each operation line.
** Adds them to each t_operation node.
** Returns the Champions exec code size. (not hex!)
*/

int			make_exc_code(t_operation **head, int *size_array)
{
	char		*encoding_byte;
	t_operation	*tmp;
	int			size;

	tmp = *head;
	size = 0;
	while (tmp)
	{
		tmp->executable = get_hex(tmp->op, 1);
		encoding_byte = NULL;
		if (g_op_tab[tmp->op].octal)
			encoding_byte = get_hex(get_encoding_byte(tmp->arg), 1);
		if (encoding_byte)
			tmp->executable = ft_strjoinfree(tmp->executable, encoding_byte);
		arg_exc_code(tmp, *head, size_array);
		size += (ft_strlen(tmp->executable) >> 1);
		tmp = tmp->next;
	}
	return (size);
}
