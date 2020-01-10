#include "vm.h"

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
		vm->champs[r1 - 1].last_live = c->last_live;
		GAME->live_counter++;
		GAME->winner = r1;
	}
	
}

void	ld(t_vm *vm, t_cursor *c, t_arg *argument)
{
	t_arg arg1;
	t_arg arg2;

	arg1 = argument[0];
	arg2 = argument[1];
	if (arg1.type == 4)
		c->registry[arg2.value - 1] = get_bytes(ARENA, get_arena_index(c->position, (arg1.value % IDX_MOD)), 4);
		// c->registry[arg2.value - 1] = get_4bytes(&ARENA[c->position + arg1.value % IDX_MOD]);
	else if (arg1.type == 2)
		c->registry[arg2.value - 1] = arg1.value;
	if (c->registry[arg2.value - 1] == 0)
			c->carry = true;
		else
			c->carry = false;
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
		c->registry[arg2.value - 1] = c->registry[arg1.value - 1];
	}
	else if (arg2.type == 4)
	{
		value = swap_32(c->registry[arg1.value - 1]);
		put_value(ARENA, get_arena_index(c->position, (arg2.value % IDX_MOD)), &value);
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
			value[i] = c->registry[argument[i].value - 1];
		if (argument[i].type == 2)
			value[i] = argument[i].value;
		if (argument[i].type == 4)
			value[i] = get_bytes(ARENA, c->position + argument[i].value % IDX_MOD, 4);
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
		if (argument[i].type == 1)
			value[i] = c->registry[argument[i].value - 1];
		if (argument[i].type == 2)
			value[i] = argument[i].value;
		if (argument[i].type == 4)
			value[i] = get_bytes(ARENA, c->position + argument[i].value % IDX_MOD, 4);
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
		if (argument[i].type == 1)
			value[i] = c->registry[argument[i].value - 1];
		if (argument[i].type == 2)
			value[i] = argument[i].value;
		if (argument[i].type == 4)
			value[i] = get_bytes(ARENA, c->position + argument[i].value % IDX_MOD, 4);
		i++;
	}
	val = value[0] ^ value[1];
	c->registry[argument[2].value - 1] = val;
	if (val == 0)
		c->carry = 1;
	else
		c->carry = 0;
}

void zjmp(t_vm *vm, t_cursor *c, t_arg *argument)
{
	if (c->carry == 0)
		return ;
	c->position = get_arena_index(c->position, argument->value % IDX_MOD);
}

void	ldi(t_vm *vm, t_cursor *c, t_arg *argument)
{
	int value[2];
	int i;

	i = 0;

	while (i < 2)
	{
		if (argument[i].type == 1)
			value[i] = c->registry[argument[i].value - 1];
		if (argument[i].type == 2)
			value[i] = argument[i].value;
		if (argument[i].type == 4)
			value[i] = get_bytes(ARENA, c->position + argument[i].value % IDX_MOD, 4);
			// value[i] = get_4bytes(&ARENA[c->position + argument[i].value % IDX_MOD]);
		i++;
	}
	c->registry[argument[2].value - 1] = get_bytes(ARENA, c->position + (value[0] + value[1]) % IDX_MOD, 4);
}

void	sti(t_vm *vm, t_cursor *c, t_arg *argument)
{
	int value[3];
	int i;

	i = 0;

	while (i < 3)
	{
		if (argument[i].type == 1)
			value[i] = c->registry[argument[i].value - 1];
		if (argument[i].type == 2)
			value[i] = argument[i].value;
		if (argument[i].type == 4)
			value[i] = get_bytes(ARENA, c->position + argument[i].value % IDX_MOD, 4);
		i++;
	}
	value[0] = swap_32(value[0]);
	put_value(ARENA, c->position + (value[1] + value[2]) % IDX_MOD, &value[0]);
}

void	lld(t_vm *vm, t_cursor *c, t_arg *argument)
{
	t_arg arg1;
	t_arg arg2;

	arg1 = argument[0];
	arg2 = argument[1];
	if (arg1.type == 4)
		c->registry[arg2.value - 1] = get_bytes(ARENA, (c->position + arg1.value) % MEM_SIZE, 4);
		// c->registry[arg2.value - 1] = get_4bytes(&ARENA[c->position + arg1.value % IDX_MOD]);
	else if (arg1.type == 2)
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
		if (argument[i].type == 1)
			value[i] = c->registry[argument[i].value - 1];
		if (argument[i].type == 2)
			value[i] = argument[i].value;
		if (argument[i].type == 4)
			value[i] = get_bytes(ARENA, c->position + argument[i].value % IDX_MOD, 4);
			// value[i] = get_4bytes(&ARENA[c->position + argument[i].value % IDX_MOD]);
		i++;
	}
	c->registry[argument[2].value - 1] = get_bytes(ARENA, (c->position + value[0] + value[1]) % MEM_SIZE, 4);
}

void	aff(t_vm *vm, t_cursor *c, t_arg *argument)
{
	char chr;

	chr = (char)(c->registry[argument[0].value - 1]);
	write(1, &chr, 1);
}

void	ft_fork(t_vm *vm, t_cursor *c, t_arg *argument, int modulo)
{
	// int i;
	t_cursor *curr;

	// i = 0;
	curr = copy_cursor(c, argument->value % modulo, GAME->cursors_id);
	// curr = new_cursor(argument[0].value % modulo, -c->id, GAME->cursors_id);
	add_cursor(&GAME->cursors, curr);
	GAME->cursors_id++;
	// while (i < 15)
	// {
	// 	curr->registry[i] = c->registry[i];
	// 	i++;
	// }
	
}

// void	lfork(t_vm *vm, t_cursor *c, t_arg *argument)
// {
// 	int i;
// 	t_cursor *curr;

// 	i = 0;
// 	curr = new_cursor(argument[0].value % MEM_SIZE, -c->id, GAME->cursors_id);
// 	add_cursor(&GAME->cursors, curr);
// 	GAME->cursors_id++;
// 	while (i < 15)
// 	{
// 		curr->registry[i] = c->registry[i];
// 		i++;
// 	}
// }

void	do_op(t_vm *vm, t_cursor *cursor, t_arg *args, int size)
{
	int	opcode;

	// print_arg(args, g_op_tab[cursor->opcode].nb_arg);/////

	opcode = cursor->opcode;
	if (opcode == 1)
		live(vm, cursor, args); // √
	else if (opcode == 2)
		ld(vm, cursor, args); // √
	else if (opcode == 3)
		st(vm, cursor, args); // √
	else if (opcode == 4)
		add(vm, cursor, args); // √
	else if (opcode == 5)
		sub(vm, cursor, args); // √
	else if (opcode == 6)
		and(vm, cursor, args); // √
	else if (opcode == 7)
		or(vm, cursor, args); // √
	else if (opcode == 8)
		xor(vm, cursor, args); // √
	else if (opcode == 9)
		zjmp(vm, cursor, args); // √
	else if (opcode == 10)
		ldi(vm, cursor, args); // √
	else if (opcode == 11)
		sti(vm, cursor, args); // √
	else if (opcode == 12)
		ft_fork(vm, cursor, args, IDX_MOD); // √
	else if (opcode == 13)
		lld(vm, cursor, args); // √
	else if (opcode == 14)
		lldi(vm, cursor, args); // √
	else if (opcode == 15)
		ft_fork(vm, cursor, args, MEM_SIZE); // √
	else if (opcode == 16)
		aff(vm, cursor, args); // √
	if (opcode != 9)
		cursor->position = get_arena_index(cursor->position, size);
	cursor->moved = true;

	// ft_printf("OPERATION EXECUTED :\n"); ///////
	// ft_printf("SIZE OF OP WAS : %d\n", size); //////
	// print_cursor(cursor, true); ///////
}