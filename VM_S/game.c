/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 14:38:02 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/14 16:51:33 by rvan-ket      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		get_opcode(t_cursor *cursor, t_byte opcode)
{
	cursor->moved = false;
	cursor->opcode = opcode;
	if (!valid_opcode(opcode))
		cursor->wait_cycles = 0;
	else
		cursor->wait_cycles = g_op_tab[opcode].cycle;
}

/*
** Loops over all the cursors and executes a command for all of them
*/

static void		cursor_operations(t_vm *vm)
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
			execute_op(vm, c);
		else if (!c->wait_cycles)
			move_cursor(vm, c, 1);
		c = c->next;
	}
}

static void		check_cursors_live(t_vm *vm, int cycles)
{
	t_cursor *c;
	t_cursor *nxt;

	c = CURSORS;
	while (c)
	{
		nxt = c->next;
		if (GAME->cycles_to_die < 1 ||
			c->last_live <= (GAME->cycles_counter - cycles))
		{
			if (vm->vflag)
				highlight_cursor(vm, c->position, -1, 0);
			CURSORS = delete_cursor(CURSORS, c->id);
			GAME->cursors_count--;
		}
		c = nxt;
	}
}

void			game(t_vm *vm)
{
	int cycles;

	vm->vflag = 1; /////////
	if (vm->vflag)
		init_vis(vm);
	cycles = 0;
	while (CURSORS)
	{
		if (!vm->vflag && vm->dump == GAME->cycles_counter)
			dump64(vm);
		cycles++;
		GAME->cycles_counter++;
		cursor_operations(vm);
		if (GAME->cycles_to_die < 1 || cycles == GAME->cycles_to_die)
		{
			GAME->checks++;
			check_cursors_live(vm, cycles);
			if (GAME->live_counter >= NBR_LIVE || GAME->checks >= MAX_CHECKS)
			{
				GAME->cycles_to_die -= CYCLE_DELTA;
				GAME->checks = 0;
			}
			GAME->check_counter += GAME->cycles_to_die;
			GAME->live_counter = 0;
			cycles = 0;
		}
		if (vm->vflag)
			refresh_windows(vm, VISUAL->arena_win, VISUAL->info_win);
	}
	if (vm->vflag)
		end_vis(vm);
	ft_printf("Contestant %d, \"%s\", has won !\n",
	GAME->winner, CHAMPS[GAME->winner - 1].name);
}
