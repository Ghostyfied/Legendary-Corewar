#include "asm.h"

/* DELATE LATER */
void			print_labels(t_label *lbl)
{
	if (!lbl)
		return ;
	ft_printf("\t%s\n", lbl->name);
	print_labels(lbl->next);
}

void			print_op(t_operation *op)
{
	if (!op)
		return ;
	ft_putendl("-----------------");
	ft_putstr("labels:\n");
	print_labels(op->labels);
	ft_printf("op id : %d\n", op->op);
	if (op->arg[0].op)
		ft_printf("arg1 : %-8s -> %d\n", op->arg[0].op, op->arg[0].arg);
	if (op->arg[1].op)
		ft_printf("arg2 : %-8s -> %d\n", op->arg[1].op, op->arg[1].arg);
	if (op->arg[2].op)
		ft_printf("arg3 : %-8s -> %d\n", op->arg[2].op, op->arg[2].arg);
	ft_putendl("-----------------");
	print_op(op->next);
}

void		print_exc_code(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		if ((i + 1) % 2 == 0)
			ft_putchar(' ');
		i++;
	}
}
