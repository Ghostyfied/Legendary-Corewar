/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operations.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-ket <rvan-ket@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 17:25:14 by rvan-ket       #+#    #+#                */
/*   Updated: 2020/01/15 13:28:05 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	do_op_next(t_vm *vm, t_cursor *cursor, t_arg *args, int size)
{
	int	opcode;

	opcode = cursor->opcode;
	if (opcode == 9)
		zjmp(vm, cursor, args);
	else if (opcode == 10)
		ldi(vm, cursor, args);
	else if (opcode == 11)
		sti(vm, cursor, args);
	else if (opcode == 12)
		ft_fork(vm, cursor, args, IDX_MOD);
	else if (opcode == 13)
		lld(vm, cursor, args);
	else if (opcode == 14)
		lldi(vm, cursor, args);
	else if (opcode == 15)
		ft_fork(vm, cursor, args, MEM_SIZE);
	else if (opcode == 16)
		aff(vm, cursor, args);
}

void	do_op(t_vm *vm, t_cursor *cursor, t_arg *args, int size)
{
	int	opcode;

	opcode = cursor->opcode;
	if (opcode == 1)
		live(vm, cursor, args);
	else if (opcode == 2)
		ld(vm, cursor, args);
	else if (opcode == 3)
		st(vm, cursor, args);
	else if (opcode == 4)
		add(vm, cursor, args);
	else if (opcode == 5)
		sub(vm, cursor, args);
	else if (opcode == 6)
		and(vm, cursor, args);
	else if (opcode == 7)
		or(vm, cursor, args);
	else if (opcode == 8)
		xor(vm, cursor, args);
	else
		do_op_next(vm, cursor, args, size);
	if (opcode != ZJUMP || (opcode == ZJUMP && !cursor->carry))
		move_cursor(vm, cursor, size);
	free(args);
}
