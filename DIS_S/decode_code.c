#include "dis.h"

short	swap_16(short nb)
{
	short b1;
	short b2;

	b1 = (nb & 0x00ff) << 8;
	b2 = (nb & 0xff00) >> 8;
	return (b1 | b2);
}

int	swap_32(int nb)
{
	int b1;
	int b2;
	int b3;
	int b4;

	b1 = (nb & 0x000000ff) << 24;
	b2 = (nb & 0x0000ff00) << 8;
	b3 = (nb & 0x00ff0000) >> 8;
	b4 = (nb & 0xff000000) >> 24;
	return (b1 | b2 | b3 | b4);
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

static int		octal_valid(t_byte octal, int nb_arg)
{
	int shift;

	if (octal & 3)
		return (0);
	if (nb_arg == 3)
		return (1);
	shift = nb_arg * 2;
	if (((octal << shift) & 0xff))
		return (0);
	return (1);
}

static int		get_arg(int fd, t_byte octal, int op_code, int *type)
{
	t_byte	b1;
	short	b2;
	int		b4;

	if ((octal & 3) == REG)
	{
		*type = T_REG;
		read(fd, &b1, 1);
		return (b1);
	}
	else if ((octal & 3) == DIR)
	{
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

/*
** Disassembler made by accident
*/

void			decode_code(int fd, t_champ *champ)
{
	t_byte		op_code;
	t_byte		octal;
	short		b2;
	int			b4;
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
		{
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
		add_operation(&champ->operations, op);
	}
}