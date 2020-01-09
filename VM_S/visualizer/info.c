#include "vm.h"

void	champ_info(t_champ champ, int y, int x, WINDOW *win)
{
	char id;

	wmove(win, y, x);
	waddstr(win, "Player ");
	waddch(win, champ.id + '0');
	waddstr(win, "\t: ");
	wattron(win, COLOR_PAIR(champ.id));
	waddstr(win, champ.name);
	wattroff(win, COLOR_PAIR(champ.id));
	wmove(win, y + 1, x);
	waddstr(win, "Last Live\t:");
	//champ.last_live
	wmove(win, y + 2, x);
	waddstr(win, "Current Lives\t:");
	//champ.lives
}

void	info_vis(t_vm *vm, WINDOW *win)
{
	char *cycles;
	char *cursors;
	int x;
	int y;
	int i;

	init_pair(INFO_C, COLOR_YELLOW, COLOR_BLACK);
	
	y = 10;
	x = 10;
	wmove(win, y, x);
	waddstr(win, "Cycles\t: ");
	cycles = ft_itoa(GAME->cycles_counter);
	free(cycles);
	wattron(win, COLOR_PAIR(INFO_C));
	waddstr(win, cycles);
	wattroff(win, COLOR_PAIR(INFO_C));

	y += 2;
	wmove(win, y, x);
	waddstr(win, "Cursors\t: ");
	cursors = ft_itoa(GAME->cursors_count);
	wattron(win, COLOR_PAIR(INFO_C));
	waddstr(win, cursors);
	wattroff(win, COLOR_PAIR(INFO_C));
	free(cursors);

	i = 0;
	while (i < vm->champion_count)
	{
		y += 5;
		champ_info(CHAMPS[i], y, x, win);
		i++;
	}
}