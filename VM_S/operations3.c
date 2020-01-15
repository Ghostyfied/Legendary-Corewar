/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operations3.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-ket <rvan-ket@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 17:27:51 by rvan-ket       #+#    #+#                */
/*   Updated: 2020/01/14 17:40:12 by rvan-ket      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	and(t_vm *vm, t_cursor *c, t_arg *argument)
{
	int value[2];
	int i;
	int	val;

	i = 0;
	while (i < 2)
	{
		if (argument[i].type == T_REG)
			value[i] = c->registry[argument[i].value - 1];
		if (argument[i].type == T_DIR)
			value[i] = argument[i].value;
		if (argument[i].type == T_IND)
			value[i] = get_bytes(ARENA,
			c->position + argument[i].value % IDX_MOD, 4);
		i++;
	}
	val = value[0] & value[1];
	c->registry[argument[2].value - 1] = val;
	if (val == 0)
		c->carry = 1;
	else
		c->carry = 0;
}

void	or(t_vm *vm, t_cursor *c, t_arg *argument)
{
	int value[2];
	int i;
	int	val;

	i = 0;
	while (i < 2)
	{
		if (argument[i].type == T_REG)
			value[i] = c->registry[argument[i].value - 1];
		if (argument[i].type == T_DIR)
			value[i] = argument[i].value;
		if (argument[i].type == T_IND)
			value[i] = get_bytes(ARENA,
			c->position + argument[i].value % IDX_MOD, 4);
		i++;
	}
	val = value[0] | value[1];
	c->registry[argument[2].value - 1] = val;
	if (val == 0)
		c->carry = 1;
	else
		c->carry = 0;
}

void	xor(t_vm *vm, t_cursor *c, t_arg *argument)
{
	int value[2];
	int i;
	int	val;

	i = 0;
	while (i < 2)
	{
		if (argument[i].type == T_REG)
			value[i] = c->registry[argument[i].value - 1];
		if (argument[i].type == T_DIR)
			value[i] = argument[i].value;
		if (argument[i].type == T_IND)
			value[i] = get_bytes(ARENA,
			c->position + argument[i].value % IDX_MOD, 4);
		i++;
	}
	val = value[0] ^ value[1];
	c->registry[argument[2].value - 1] = val;
	if (val == 0)
		c->carry = 1;
	else
		c->carry = 0;
}

void	zjmp(t_vm *vm, t_cursor *c, t_arg *argument)
{
	if (c->carry == 0)
		return ;
	move_cursor(vm, c, (argument->value % IDX_MOD));
}

void	ldi(t_vm *vm, t_cursor *c, t_arg *argument)
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
			value[i] = get_bytes(ARENA, get_arena_index(c->position,
			argument[i].value % IDX_MOD), 4);
		i++;
	}
	c->registry[argument[2].value - 1] = get_bytes(ARENA,
	get_arena_index(c->position, (value[0] + value[1]) % IDX_MOD), 4);
}
