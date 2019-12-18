#include "vm.h"

static void		setup_cursors(t_vm *vm)
{
	int		i;
	t_champ	c;

	i = 0;
	while (i < vm->champion_count)
	{
		c = CHAMPS[i];
		add_cursor(&GAME->cursors, new_cursor(c.starting_pos, -c.id, GAME->cursors_id));
		GAME->cursors_id++;
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
	print_cursors(GAME->cursors);
	// print_champions(CHAMPS, vm->champion_count);
}
