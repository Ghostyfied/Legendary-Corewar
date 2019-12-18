#include "vm.h"

void			play_game(t_vm *vm)
{
	while (GAME->cycles < GAME->cycles_to_die)
	{
		GAME->cycles = (GAME->cycles + 1) % GAME->cycles_to_die;
	}
}
