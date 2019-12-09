#include "asm.h"

/*
** Using bitwise operators gets the correct encoding byte.
** T_REG = 01 (1)
** T_DIR = 10 (2)
** T_IND = 11 (3)
*/

static int		get_encoding_byte(int arg1, int arg2, int arg3)
{
	t_byte byte;

	byte = 0;
	byte = byte | arg1;
	byte = (byte << 2) | arg2;
	byte = (byte << 2) | arg3;
	byte <<= 2;
	return (byte);
}

/*
** Returns a string with size bytesize.
** String contains the hex of nb.
*/

static char		*get_hex(unsigned int nb, int bytesize)
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

/*
** Uses the int *size to add up the byte dist from the label name to the arg using the label.
** If label(index) is bigger then the arg(index) then step = -1.
** Add all the operation sizes until label(index) is the same as arg(index).
** Returns the amount of bytes from label to arg.
** Can be negative depending if label was called before or after arg.
*/

static int		calc_bytes_dist(int *size, int label, int arg)
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

/*
** Finds and calculates the amount of bytes from arg:label to label:operation the cursor has to jump in the VM.
*/

static int		find_label(t_operation *op, char *label, int size_idx, int *size)
{
	t_label		*lbl;

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
	ft_error("Label doesn't exist");
	return (-1);
}

/*
** Returns hex string for each argument.
*/

static char		*get_arg(t_operation *head, t_arg arg, t_operation *op, int *size)
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
		s = get_hex(value, op_tab[op->op].dir_size);
	return (s);
}

/*
** Gets all hex strings for each operation line.
** Adds them to each t_operation node.
*/

void			make_exc_code(t_operation **head, int *size_array)
{
	char		*operation_code;
	char		*encoding_byte;
	char		*args;
	t_operation	*tmp;
	int			i;

	tmp = *head;
	while (tmp)
	{
		i = 0;
		operation_code = get_hex(tmp->op, 1);
		encoding_byte = NULL;
		if (op_tab[tmp->op].octal)
			encoding_byte = get_hex(get_encoding_byte(tmp->arg[0].arg, tmp->arg[1].arg, tmp->arg[2].arg), 1);
		tmp->executable = operation_code;
		if (encoding_byte)
			tmp->executable = ft_strjoinfree(tmp->executable, encoding_byte);
		while (i < 3)
		{
			args = get_arg(*head, tmp->arg[i], tmp, size_array);
			if (args)
				tmp->executable = ft_strjoinfree(tmp->executable, args);
			i++;
		}
		print_exc_code(tmp->executable);
		tmp = tmp->next;
	}
}
