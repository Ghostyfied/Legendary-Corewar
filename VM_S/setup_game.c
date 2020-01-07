/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 15:51:45 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/07 15:53:27 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		setup_cursors(t_vm *vm)
{
	int		i;
	t_champ	c;

	i = 0;
	while (i < vm->champion_count)
	{
		c = CHAMPS[i];
		add_cursor(&GAME->cursors,
					new_cursor(c.starting_pos, -c.id, GAME->cursors_id));
		GAME->cursors_id++;
		i++;
	}
}

static void		introduction(t_champ *champs, int nb_champs)
{
	int i;

	i = 0;
	ft_putendl("Introducing contestants...");
	while (i < nb_champs)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		champs[i].id, champs[i].code_size, champs[i].name, champs[i].comment);
		i++;
	}
}

void			setup_game(t_vm *vm)
{
	GAME = MEM(t_game);
	GAME->winner = vm->champion_count;
	GAME->cycles_to_die = CYCLE_TO_DIE;
	GAME->cursors_id = 1;
	setup_cursors(vm);
	introduction(CHAMPS, vm->champion_count);
}
