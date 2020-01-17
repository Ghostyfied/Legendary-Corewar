/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operations2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-ket <rvan-ket@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 17:27:16 by rvan-ket       #+#    #+#                */
/*   Updated: 2020/01/17 15:31:42 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	live(t_vm *vm, t_cursor *c, t_arg *arg)
{
	arg->value = -arg->value;
	c->last_live = vm->game->cycles_counter;
	if (arg->value > 0 && arg->value <= vm->champ_nb)
	{
		CHAMPS[arg->value - 1].lives++;
		CHAMPS[arg->value - 1].last_live = c->last_live;
		GAME->winner = arg->value;
		GAME->live_counter++;
	}
}

void	ld(t_vm *vm, t_cursor *c, t_arg *argument)
{
	t_arg arg1;
	t_arg arg2;

	arg1 = argument[0];
	arg2 = argument[1];
	if (arg1.type == T_IND)
		c->registry[arg2.value - 1] = get_bytes(ARENA,
		get_arena_index(c->position, (arg1.value % IDX_MOD)), 4);
	else if (arg1.type == T_DIR)
		c->registry[arg2.value - 1] = arg1.value;
	if (c->registry[arg2.value - 1] == 0)
		c->carry = true;
	else
		c->carry = false;
}

void	st(t_vm *vm, t_cursor *c, t_arg *argument)
{
	t_arg	arg1;
	t_arg	arg2;
	int		value;
	int		index;

	arg1 = argument[0];
	arg2 = argument[1];
	if (arg2.type == T_REG)
		c->registry[arg2.value - 1] = c->registry[arg1.value - 1];
	else if (arg2.type == T_IND)
	{
		value = swap_32(c->registry[arg1.value - 1]);
		index = get_arena_index(c->position, (arg2.value % IDX_MOD));
		put_value(ARENA, index, &value);
		if (vm->vflag)
			update_arena(vm, index, VISUAL->carena[c->position]);
	}
}

void	add(t_cursor *c, t_arg *argument)
{
	t_arg	arg1;
	t_arg	arg2;
	t_arg	arg3;
	int		value;

	arg1 = argument[0];
	arg2 = argument[1];
	arg3 = argument[2];
	value = c->registry[arg1.value - 1] + c->registry[arg2.value - 1];
	c->registry[arg3.value - 1] = value;
	if (value == 0)
		c->carry = 1;
	else
		c->carry = 0;
}

void	sub(t_cursor *c, t_arg *argument)
{
	t_arg	arg1;
	t_arg	arg2;
	t_arg	arg3;
	int		value;

	arg1 = argument[0];
	arg2 = argument[1];
	arg3 = argument[2];
	value = c->registry[arg1.value - 1] - c->registry[arg2.value - 1];
	c->registry[arg3.value - 1] = value;
	if (value == 0)
		c->carry = 1;
	else
		c->carry = 0;
}
