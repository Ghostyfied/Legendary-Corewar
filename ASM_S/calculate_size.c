#include "asm.h"

void		print_labels(t_label *lbl)
{
	if (!lbl)
		return ;
	ft_printf("\t%s\n", lbl->name);
	print_labels(lbl->next);
}

void		print_op(t_operation *op)
{
	if (!op)
		return ;
	ft_putendl("-----------------");
	ft_putstr("labels:\n");
	print_labels(op->labels);
	ft_printf("op id : %d\n", op->op);
	if (op->arg[0].op)
		ft_printf("arg1 : %s\n", op->arg[0].op);
	if (op->arg[1].op)
		ft_printf("arg2 : %s\n", op->arg[1].op);
	if (op->arg[2].op)
		ft_printf("arg3 : %s\n", op->arg[2].op);
	ft_putendl("-----------------");
	print_op(op->next);

}

static void	ft_print_byte(const t_byte *byte, size_t size)
{
	int					idx;
	size_t				i;
	const unsigned char	*b;

	i = 0;
	b = (const t_byte *)byte;
	while (i < size)
	{
		idx = 7;
		while (idx >= 0)
		{
			if ((b[i] & (1 << idx)) != 0)
				write(1, "1", 1);
			else
				write(1, "0", 1);
			idx--;
		}
		i++;
	}
	ft_putendl("");
}

static int	get_encoding_byte(int arg1, int arg2, int arg3)
{
	t_byte byte;

	byte = 0;
	byte = byte | arg1;
	byte = (byte << 2) | arg2;
	byte = (byte << 2) | arg3;
	byte <<= 2;
	ft_print_byte(&byte, 1);
	return (byte);
}

static char *get_hex(int nb, int size)
{
	char *hex;

	hex = ft_strnew(size);
	ft_putendl(hex);
	return (hex);
}

void		calculate_size(t_operation **operations)
{
	char *op;
	t_byte	oct;
	int		arg;

	get_encoding_byte(T_REG, T_DIR, T_DIR);
	// get_encoding_byte(T_REG, T_DIR, T_DIR);
	// get_encoding_byte(T_REG, T_DIR, T_DIR);
	// ft_printf("%s\n", op_tab[(*operations)->op].name);
	if (op_tab[(*operations)->op].octal)
	{
		// Get octal
		;
	}
	print_op(*operations);
}