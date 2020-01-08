#include "vm.h"


void			put_value(t_byte *arena, int idx, void *value)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		arena[get_arena_index(idx, i)] = ((t_byte*)value)[i];
		i++;
	}
}

/* add size // big andian?*/


 /*nog niet getest */
void	live(t_vm *vm, t_cursor *c, t_arg *argument)
{
	int r1;

	r1 = c->registry[0] * -1;
	if (r1 > 0 && r1 <= vm->champ_nb && -r1 == argument->value)
	{
		vm->champs[r1 - 1].lives++;
		c->last_live = vm->game->cycles_counter;
		GAME->live_counter++;
	}
	
}

void	ld(t_vm *vm, t_cursor *c, t_arg *argument)
{
	t_arg arg1;
	t_arg arg2;

	arg1 = argument[0];
	arg2 = argument[1];
	if (arg1.type == 4)
	{
		c->registry[arg2.value - 1] = get_4bytes(&ARENA[c->position + arg1.value % IDX_MOD]);
		if (c->registry[arg2.value - 1] == 0)
			c->carry = 1;
		else
			c->carry = 0;
	}
	else if (arg1.type == 2)
	{
		ft_memcpy(&c->registry[arg2.value - 1], &arg1.value, 4);
		if (arg1.value == 0)
			c->carry = 0;
		else
			c->carry = 1;
	}
}

/* not sure of die IDX_MOD daar juist is brobro*/
void	st(t_vm *vm, t_cursor *c, t_arg *argument)
{
	t_arg arg1;
	t_arg arg2;
	int value;

	arg1 = argument[0];
	arg2 = argument[1];

	if (arg2.type == 1)
	{
		// ft_memcpy(&c->registry[arg2.value - 1], &arg1.value, 4);
		c->registry[arg2.value - 1] = arg1.value;
	}
	else if (arg2.type == 4)
	{
		value = swap_32(c->registry[arg1.value - 1]);
		ft_memcpy(&ARENA[(c->position + arg2.value % IDX_MOD) % IDX_MOD], &value, 4);
		// swap_32();
	}
}

 /*nog niet getest */
void	add(t_vm *vm, t_cursor *c, t_arg *argument)
{
	t_arg arg1;
	t_arg arg2;
	t_arg arg3;
	int value;

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

 /*nog niet getest */
void	sub(t_vm *vm, t_cursor *c, t_arg *argument)
{
	t_arg arg1;
	t_arg arg2;
	t_arg arg3;
	int value;

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

 /*nog niet getest  en type=4 i dunno of da weirkt a bro*/
void	and(t_vm *vm, t_cursor *c, t_arg *argument)
{
	int value[2];
	int i;
	int	val;

	i = 0;
	while (i < 2)
	{
		if (argument[i].type == 1)
			value[i] = c->registry[argument[i].value];
		if (argument[i].type == 2)
			value[i] = argument[i].value;
		if (argument[i].type == 4)
			ft_memcpy(&value[i], &ARENA[c->position + argument[i].value % IDX_MOD], 4);		
		i++;
	}
	val = value[0] & value[1];
	ft_memcpy(&c->registry[argument[2].value], &val, 4);
}

void	or(t_vm *vm, t_cursor *c, t_arg *argument)
{
	int value[2];
	int i;
	int	val;

	i = 0;
	while (i < 2)
	{
		if (argument[i].type == 1)
			value[i] = c->registry[argument[i].value];
		if (argument[i].type == 2)
			value[i] = argument[i].value;
		if (argument[i].type == 4)
			ft_memcpy(&value[i], &ARENA[c->position + argument[i].value % IDX_MOD], 4);		
		i++;
	}
	val = value[0] | value[1];
	c->registry[argument[2].value - 1] = val;
}

void	xor(t_vm *vm, t_cursor *c, t_arg *argument)
{
	int value[2];
	int i;
	int	val;

	i = 0;
	while (i < 2)
	{
		if (argument[i].type == 1)
			value[i] = c->registry[argument[i].value];
		if (argument[i].type == 2)
			value[i] = argument[i].value;
		if (argument[i].type == 4)
			ft_memcpy(&value[i], &ARENA[c->position + argument[i].value % IDX_MOD], 4);		
		i++;
	}
	val = value[0] ^ value[1];
	ft_memcpy(&c->registry[argument[2].value], &val, 4);
}

void zjmp(t_vm *vm, t_cursor *c, t_arg *argument)
{
	if (c->carry == 0)
		return ;
	if (argument->value < 0)
		c->position -= argument->value % IDX_MOD;
	else
		c->position += argument->value % IDX_MOD;
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
	else if (opcode == 9)
		zjmp(vm, cursor, args);
	// else if (opcode == 10)
	// 	ldi(vm, cursor, args);
	// else if (opcode == 11)
	// 	sti(vm, cursor, args);
	// else if (opcode == 12)
	// 	ftfork(vm, cursor, args);
	// else if (opcode == 13)
	// 	lld(vm, cursor, args);
	// else if (opcode == 14)
	// 	lldi(vm, cursor, args);
	// else if (opcode == 15)
	// 	lfork(vm, cursor, args);
	// else if (opcode == 16)
	// 	aff(vm, cursor, args);
	// ft_memcpy(ARENA[c->pos +/- x], value, 4);
	cursor->position += size;
	cursor->moved = true;
}