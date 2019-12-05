#include "asm.h"

void		print_labels(t_label *lbl)
{
	if (!lbl)
		return ;
	print_labels(lbl->next);
	ft_printf("\t%s\n", lbl->name);
}

void		print_op(t_operation *op)
{
	if (!op)
		return ;
	print_op(op->next);
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

}

void		calculate_size(t_operation **operations)
{
	char *op;
	t_byte	oct;
	int		arg;
	if (op_tab[(*operations)->op].octal)
	{
		// Get octal
		;
	}
	print_op(*operations);
}