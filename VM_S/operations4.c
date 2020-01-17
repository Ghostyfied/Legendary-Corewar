/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operations4.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-ket <rvan-ket@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 17:32:00 by rvan-ket       #+#    #+#                */
/*   Updated: 2020/01/17 15:32:51 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	sti(t_vm *vm, t_cursor *c, t_arg *argument)
{
	int value[3];
	int i;
	int idx;

	i = 0;
	while (i < 3)
	{
		if (argument[i].type == T_REG)
			value[i] = c->registry[argument[i].value - 1];
		if (argument[i].type == T_DIR)
			value[i] = argument[i].value;
		if (argument[i].type == T_IND)
			value[i] = get_bytes(ARENA,
			get_arena_index(c->position, argument[i].value % IDX_MOD), 4);
		i++;
	}
	value[0] = swap_32(value[0]);
	idx = get_arena_index(c->position, (value[1] + value[2]) % IDX_MOD);
	put_value(ARENA, idx, &value[0]);
	if (vm->vflag)
		update_arena(vm, idx, VISUAL->carena[c->position]);
}

void	lld(t_vm *vm, t_cursor *c, t_arg *argument)
{
	t_arg arg1;
	t_arg arg2;

	arg1 = argument[0];
	arg2 = argument[1];
	if (arg1.type == T_IND)
		c->registry[arg2.value - 1] = get_bytes(ARENA,
		get_arena_index(c->position, arg1.value), 4);
	else if (arg1.type == T_DIR)
		c->registry[arg2.value - 1] = arg1.value;
	if (c->registry[arg2.value - 1] == 0)
		c->carry = 1;
	else
		c->carry = 0;
}

void	lldi(t_vm *vm, t_cursor *c, t_arg *argument)
{
	int value[2];
	int i;

	i = 0;
	while (i < 2)
	{
		if (argument[i].type == T_REG)
			value[i] = c->registry[argument[i].value - 1];
		if (argument[i].type == T_DIR)
			value[i] = argument[i].value;
		if (argument[i].type == T_IND)
			value[i] = get_bytes(ARENA,
			get_arena_index(c->position, argument[i].value % IDX_MOD), 4);
		i++;
	}
	c->registry[argument[2].value - 1] = get_bytes(ARENA,
	get_arena_index(c->position, (value[0] + value[1]) % MEM_SIZE), 4);
}

void	aff(t_cursor *c, t_arg *argument)
{
	char chr;

	chr = (char)(c->registry[argument[0].value - 1]);
	write(1, &chr, 1);
}

void	ft_fork(t_vm *vm, t_cursor *c, t_arg *argument, int modulo)
{
	t_cursor *curr;

	curr = copy_cursor(c,
	get_arena_index(c->position, argument->value % modulo), GAME->cursors_id);
	add_cursor(&GAME->cursors, curr);
	GAME->cursors_id++;
	GAME->cursors_count++;
	if (vm->vflag)
		highlight_cursor(vm, -1, curr->position);
}
