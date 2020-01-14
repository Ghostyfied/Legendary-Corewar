#include "vm.h"

void	paused(WINDOW *win)
{
	mvwaddstr(win, 5, 10, "PAUSED ");
	curs_set(0);
	wrefresh(win);
	while (getch() != ' ')
		;
}

void	champ_info(t_champ champ, int y, int x, WINDOW *win)
{
	char	*last_live;
	char	*total_lives;

	wmove(win, y, x);
	waddstr(win, "Player ");
	waddch(win, champ.id + '0');
	waddstr(win, "\t: ");
	wattron(win, COLOR_PAIR(champ.id));
	waddstr(win, champ.name);
	wattroff(win, COLOR_PAIR(champ.id));
	wmove(win, y + 2, x);
	waddstr(win, "Last Live\t: ");
	last_live = ft_itoa(champ.last_live);
	wattron(win, COLOR_PAIR(champ.id));
	waddstr(win, last_live);
	wattroff(win, COLOR_PAIR(champ.id));
	free(last_live);
	wmove(win, y + 3, x);
	waddstr(win, "Total Lives\t: ");
	total_lives = ft_itoa(champ.lives);
	wattron(win, COLOR_PAIR(champ.id));
	waddstr(win, total_lives);
	wattroff(win, COLOR_PAIR(champ.id));
	free(total_lives);
}

void	info_vis(t_vm *vm, WINDOW *win)
{
	char *cycles;
	char *cursors;
	char *check;
	int y;
	int x;
	int i;

	mvwaddstr(win, 5, 10, "RUNNING");
	y = 10;
	x = 10;

	wmove(win, y, x);
	waddstr(win, "Cycles\t: ");
	cycles = ft_itoa(GAME->cycles_counter);
	waddstr(win, cycles);
	free(cycles);

	wmove(win, y + 2, x);
	waddstr(win, "Check at\t: ");
	check = ft_itoa(GAME->check_counter);
	waddstr(win, check);
	free(check);
	wmove(win, y + 3, x);
	waddstr(win, "Check every\t: ");
	check = ft_itoa(GAME->cycles_to_die);
	waddstr(win, check);
	free(check);

	y += 5;
	wmove(win, y, x);
	waddstr(win, "Cursors\t: ");
	cursors = ft_itoa(GAME->cursors_count);
	waddstr(win, cursors);
	free(cursors);

	i = 0;
	while (i < vm->champion_count)
	{
		y += 5;
		champ_info(CHAMPS[i], y, x, win);
		i++;
	}
	if (!CURSORS)
	{
		mvwaddstr(win, y + 15, x + 5, "*** WINNER : ");
		wattron(win, COLOR_PAIR(GAME->winner));
		waddstr(win, CHAMPS[GAME->winner - 1].name);
		wattroff(win, COLOR_PAIR(GAME->winner));
		waddstr(win, " ***");
	}
}
