#include "asm.h"

static int	get_encoding_byte(int arg1, int arg2, int arg3)
{
	t_byte byte;

	byte = 0;
	byte = byte | arg1;
	byte = (byte << 2) | arg2;
	byte = (byte << 2) | arg3;
	byte <<= 2;
	return (byte);
}

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

static char		*get_arg(t_operation *head, t_arg arg, t_operation *op, int *size)
{
	char	*s;
	int		value;
	char	*lbl;

	s = "";
	if (!arg.arg)
		return (s);
	value = ft_atoi(&arg.op[1]);
	if (arg.arg == T_REG)
		return (get_hex(value, 1));
	lbl = ft_strchr(arg.op, LABEL_CHAR);
	if (lbl)
		value = find_label(head, ++lbl, op->size_index, size);
	else if (arg.arg == T_IND)
		value = ft_atoi(arg.op);
	if (arg.arg == T_IND)
		s = get_hex(value, 2);
	else if (arg.arg == T_DIR)
		s = get_hex(value, op_tab[op->op].dir_size);
	return (s);
}

void			make_exc_code(t_operation **head, int *size_array)
{
	char	*operation_code;
	char	*encoding_byte;
	char	*arg1;
	char	*arg2;
	char	*arg3;
	int		size;
	t_operation *tmp;

	tmp = *head;
	while (tmp)
	{
		operation_code = get_hex(tmp->op, 1);
		if (op_tab[tmp->op].octal)
			encoding_byte = get_hex(get_encoding_byte(tmp->arg[0].arg, tmp->arg[1].arg, tmp->arg[2].arg), 1);
		else
			encoding_byte = "";
		arg1 = get_arg(*head, tmp->arg[0], tmp, size_array);
		arg2 = get_arg(*head, tmp->arg[1], tmp, size_array);
		arg3 = get_arg(*head, tmp->arg[2], tmp, size_array);
		size = ft_strlen(operation_code) + ft_strlen(encoding_byte) + ft_strlen(arg1) + ft_strlen(arg2) + ft_strlen(arg3);
		ft_printf("%s %s %s %s %s\n", operation_code, encoding_byte, arg1, arg2, arg3);
		tmp = tmp->next;
	}
}
