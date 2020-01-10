/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 14:38:02 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/10 18:26:39 by fhignett      ########   odam.nl         */
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
		{
			get_opcode(c, ARENA[c->position]);
			if (vm->vflag)
				highlight_cursor(vm, c, ATTR);
		}
		if (c->wait_cycles > 0)
			c->wait_cycles--;
		if (c->wait_cycles == 0 && valid_opcode(c->opcode))
			execute_op(vm, c);
		else if (!c->wait_cycles)
		{
			if (vm->vflag)
				highlight_cursor(vm, c, A_NORMAL);
			c->position = get_arena_index(c->position, 1);
			c->moved = true;
		}
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
				highlight_cursor(vm, c, A_NORMAL);
			CURSORS = delete_cursor(CURSORS, c->id);
		}
		c = nxt;
	}
}

void			game(t_vm *vm)
{
	int cycles;

	vm->vflag = 1;/////////
	if (vm->vflag)
		init_vis(vm);
	cycles = 0;
	while (CURSORS)
	{
		if (!vm->vflag && vm->dump == GAME->cycles_counter)
			dump64(vm);
		cursor_operations(vm);
		if (GAME->cycles_to_die < 1 || cycles == GAME->cycles_to_die)
		{
			GAME->checks++;
			check_cursors_live(vm, cycles);
			if (GAME->live_counter >= NBR_LIVE || GAME->checks > MAX_CHECKS)
			{
				GAME->cycles_to_die -= CYCLE_DELTA;
				GAME->checks = 0;
			}
			GAME->live_counter = 0;
			cycles = 0;
			// reset_champs_lives
		}
		if (vm->vflag)
			refresh_windows(VISUAL->arena_win, VISUAL->info_win);
		cycles++;
		GAME->cycles_counter++;
	}
	if (vm->vflag)
		end_vis();
	ft_printf("Contestant %d, \"%s\", has won !\n",
	GAME->winner, CHAMPS[GAME->winner - 1].name);
}
