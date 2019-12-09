#include "asm.h"

static int		get_arg_size(t_arg arg, int op)
{
	int size;

	size = 0;
	if (!arg.arg)
		return (size);
	if (arg.arg == T_REG)
		size = 1;
	else if (arg.arg == T_IND)
		size = 2;
	else if (arg.arg == T_DIR)
		size = op_tab[op].dir_size;
	return (size);
}

/*
** Calculates the size of each operation line.
*/

void			calculate_size(t_operation *op, int **byte_size, int i)
{
	int size;

	if (!op)
		return ;
	calculate_size(op->next, byte_size, i + 1);
	size = 1;
	if (op_tab[op->op].octal)
		size++;
	size += get_arg_size(op->arg[0], op->op);
	size += get_arg_size(op->arg[1], op->op);
	size += get_arg_size(op->arg[2], op->op);
	(*byte_size)[i] = size;
}
