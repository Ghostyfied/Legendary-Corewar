#include "vm.h"

static void	print_operations(t_operation *op)
{
	int		i;
	char	*s;

	if (!op)
		return ;
	ft_printf("%-10s : %d (%s)\n", "op_code", op->op_code, g_op_tab[op->op_code].name);
	ft_printf("%-10s : %d\n\t\t", "nb_arg", op->nb_arg);
	i = 0;
	while (i < op->nb_arg)
	{
		s = op->args[i].type == T_DIR ? "T_DIR" : op->args[i].type == T_REG ? "T_REG" : "T_IND";
		ft_printf("%s : %d, ", s, op->args[i].value);
		i++;
	}
	ft_putendl("");
	print_operations(op->next);
}

void	print_champions(t_champ *champs, int champ_nb)
{
	int i;

	i = 0;
	while (i < champ_nb)
	{
		ft_printf("%d\n", champs[i].nb_set);
		ft_printf("%-10s : %s\n", ".name", champs[i].name);
		ft_printf("%-10s : %s\n", ".comment", champs[i].comment);
		ft_printf("%-10s : %d\n", "code_size", champs[i].code_size);
		print_operations(champs[i].operations);
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
