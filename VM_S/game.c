#include "vm.h"

int			valid_opcode(t_byte opcode)
{
	if (opcode < 1 || opcode > 16)
		return (0);
	return (1);
}

/*
** EXAMPLE:
** int x = get_Xbytes(&ARENA[i]); index vanaf waar je de bytes wilt lezen, geeft een integer terug in kleine endian!
*/

int			get_2bytes(t_byte *arena)
{
	short b;

	ft_memcpy(&b, arena, 2);
	return (swap_16(b));
}

int			get_4bytes(t_byte *arena)
{
	int b;

	ft_memcpy(&b, arena, 4);
	return (swap_32(b));
}

void		get_opcode(t_cursor *cursor, t_byte opcode)
{
	cursor->moved = false;
	cursor->opcode = opcode;
	if (!valid_opcode(opcode))
		cursor->wait_cycles = 0;
	else
		cursor->wait_cycles = g_op_tab[opcode].cycle;
}

int			octal_valid(t_byte octal, int nb_arg)
{
	int shift;

	if (octal & 3)
		return (0);
	if (nb_arg == 3)
		return (1);
	shift = nb_arg * 2;
	if (((octal << shift) & 0xff))
		return (0);
	return (1);
}

t_arg		get_arg(t_byte opcode, t_byte arg_type)
{
	t_arg arg;

	if ((arg_type & 3) == REG)
	{
		arg.size = 1;
		arg.type = T_REG;
		return (arg);
	}
	else if ((arg_type & 3) == DIR)
	{
		arg.size = g_op_tab[opcode].dir_size;
		arg.type = T_DIR;
		return (arg);
	}
	else
	{
		arg.size = 2;
		arg.type = T_IND;
		return (arg);
	}
}

t_arg		*get_args(t_cursor *c, t_byte octal, t_byte *arena)
{
	t_arg *args;
	int shift;
	int i;
	int op_idx;

	op_idx = 2; /* Skips opcode and octal */
	shift = 6;
	i = 0;
	args = (t_arg*)ft_memalloc(sizeof(t_arg) * g_op_tab[c->opcode].nb_arg);
	while (i < g_op_tab[c->opcode].nb_arg)
	{
		args[i] = get_arg(c->opcode, ((octal >> shift) & 3));
		if (args[i].size == 1)
			args[i].value = arena[c->position + op_idx];
		else if (args[i].size == 2)
			args[i].value = get_2bytes(&arena[c->position + op_idx]);
		else
			args[i].value = get_4bytes(&arena[c->position + op_idx]);
		shift -= 2;
		op_idx += args[i].size;
		i++;
	}
	return (args);
}

int			get_size(t_byte opcode, t_byte octal, int nb_arg)
{
	int shift;
	int i;
	int size;

	shift = 6;
	i = 0;
	size = 0;
	while (i < nb_arg)
	{
		if (((octal >> shift) & 3) == REG)
			size += 1;
		else if (((octal >> shift) & 3) == DIR)
			size += g_op_tab[opcode].dir_size;
		else if (((octal >> shift) & 3) == IND)
			size += 2;
		i++;
		shift -= 2;
	}
	return (size);
}

void		execute_op(t_cursor *c, t_vm *vm)
{
	int i;
	int size;
	t_arg *args;

	if (g_op_tab[c->opcode].octal)
	{
		size = get_size(c->opcode, ARENA[c->position + 1], g_op_tab[c->opcode].nb_arg) + 2;
		if (!octal_valid(ARENA[c->position + 1], g_op_tab[c->opcode].nb_arg))
		{
			c->position += size;
			return ;
		}
		args = get_args(c, ARENA[c->position + 1], ARENA);
		i = 0;
		while (i < g_op_tab[c->opcode].nb_arg)
		{
			if ((args[i].type == T_REG && (args[i].value < 1 || args[i].value > 16)) ||
				!(args[i].type & g_op_tab[c->opcode].args[i]))
			{
				free(args);
				c->position += size;
				return ;
			}
			i++;
		}
		// do_op(vm, c, args, size);
	}
	else
	{
		args = MEM(t_arg);
		size = 1 + g_op_tab[c->opcode].dir_size;
		args->size = g_op_tab[c->opcode].dir_size;
		args->value = args->size == 4 ? get_4bytes(&ARENA[c->position + 1]) : get_2bytes(&ARENA[c->position + 1]);
		if (args->value < 1 || args->value > 16)
		{
			free(args);
			c->position += size;
			return ;
		}
		args->type = T_DIR;
		// do_op(vm, c, args, size);
	}
}

void		loop_cursors(t_vm *vm)
{
	t_cursor *c;

	c = CURSORS;
	while (c)
	{
		if (c->moved)
			get_opcode(c, ARENA[c->position]);
		if (c->wait_cycles > 0)
			c->wait_cycles--;
		if (c->wait_cycles == 0 && valid_opcode(c->opcode))
			execute_op(c, vm);
		else if (!c->wait_cycles)
		{
			c->position = (c->position + 1) % MEM_SIZE;
			c->moved = true;
		}
		c = c->next;
	}
}

void		game(t_vm *vm)
{
	// while (CURSORS)
	// {
		loop_cursors(vm);
	// }
}