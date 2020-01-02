#include "vm.h"

/*
** EXAMPLES:
** int x = get_Xbytes(&ARENA[i]); index vanaf waar je de bytes wilt lezen, geeft een integer terug in kleine endian!
*/

int			valid_opcode(t_byte opcode)
{
	if (opcode < 1 || opcode > 16)
		return (0);
	return (1);
}

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

int			*get_args(int op_code, t_byte octal, int nb_arg)
{
	if (!octal_valid(octal, nb_arg))
		; // Cursor must be moved to the next operation without execution
	// t_arg	*args;
	// int		i;
	// int		shift;

	// *nb_arg = g_op_tab[op_code].nb_arg;
	// args = (t_arg*)ft_memalloc(sizeof(t_arg) * *nb_arg);
	// i = 0;
	// shift = 6;
	// while (i < *nb_arg)
	// {
	// 	args[i].value = get_arg(fd, octal >> shift, op_code, &args[i].type);
	// 	shift -= 2;
	// 	i++;
	// }
	return (0);
}

void		execute_op(t_cursor *c, t_byte *arena)
{
	int i;
	int	*args;

	i = 0;
	if (g_op_tab[c->opcode].octal)
	{
		// args = get_args(c->opcode, arena[i], g_op_tab[c->opcode].nb_arg);
		;

	}
	else
	{
		if (g_op_tab[c->opcode].dir_size == 2)
			// get_2bytes();
			;
		else
			// get_4bytes();
			;
		
	}
}

void		loop_cursors(t_vm *vm)
{
	t_cursor *c;

	c = GAME->cursors;
	while (c)
	{
		if (c->moved)
			get_opcode(c, ARENA[c->position]);
		if (c->wait_cycles > 0)
			c->wait_cycles--;
		if (c->wait_cycles == 0 && valid_opcode(c->opcode))
			execute_op(c, &ARENA[(c->position + 1)]);
		else if (!c->wait_cycles)
		{
			c->position = (c->position + 1) % MEM_SIZE;
			c->moved = true;
		}
		// print_cursor(c, false);
		c = c->next;
	}
}