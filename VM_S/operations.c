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
		c->registry[arg2.value - 1] = get_bytes(ARENA, c->position + arg1.value % IDX_MOD, 4);
		// c->registry[arg2.value - 1] = get_4bytes(&ARENA[c->position + arg1.value % IDX_MOD]);
	else if (arg1.type == 2)
		c->registry[arg2.value - 1] = arg1.value;
	if (c->registry[arg2.value - 1] == 0)
			c->carry = 1;
		else
			c->carry = 0;
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
			value[i] = c->registry[argument[i].value - 1];
		if (argument[i].type == 2)
			value[i] = argument[i].value;
		if (argument[i].type == 4)
			ft_memcpy(&value[i], &ARENA[c->position + argument[i].value % IDX_MOD], 4);		
		i++;
	}
	val = value[0] & value[1];
	ft_memcpy(&c->registry[argument[2].value - 1], &val, 4);
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
		{
			val = swap_32(ARENA[c->position + argument[i].value % IDX_MOD]);
			ft_memcpy(&value[i], &val, 4);		
		}
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
			ft_memcpy(&value[i], &ARENA[c->position + argument[i].value % IDX_MOD], 4);		
		i++;
	}
	val = value[0] ^ value[1];
	ft_memcpy(&c->registry[argument[2].value - 1], &val, 4);
	if (val == 0)
		c->carry = 1;
	else
		c->carry = 0;
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

void	ldi(t_vm *vm, t_cursor *c, t_arg *argument)
{
	int value[2];
	int i;

	i = 0;
	// ft_printf("hierzo 22xd \n");

	while (i < 2)
	{
		// ft_printf("hierzo xd \n");

		if (argument[i].type == 1)
			value[i] = c->registry[argument[i].value - 1];
		if (argument[i].type == 2)
			value[i] = argument[i].value;
		if (argument[i].type == 4)
			value[i] = get_bytes(ARENA, c->position + argument[i].value % IDX_MOD, 4);
			// value[i] = get_4bytes(&ARENA[c->position + argument[i].value % IDX_MOD]);
		i++;
	}
	// ft_printf("hierzo xd \n");
	c->registry[argument[2].value - 1] = get_bytes(ARENA, c->position + (value[0] + value[1]) % IDX_MOD, 4);
	// c->registry[argument[2].value - 1] = get_4bytes(&ARENA[c->position + (value[0] + value[1]) % IDX_MOD]);

}

/*
** GOEIEMORGE ROBBE!!! 
** NIEUWE FUNCTIE ALERT: get_bytes(ARENA, int : current idx, int : amount of bytes you want to get) -> return(int : little endian AKA niks aan doen)
** LUV
*/

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
	else if (opcode == 10)
		ldi(vm, cursor, args);
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
	cursor->position += size;
	cursor->moved = true;
}