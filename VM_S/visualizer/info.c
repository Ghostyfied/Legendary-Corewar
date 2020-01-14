/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   info.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 16:39:15 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/14 16:54:19 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	char	*info;

	mvwaddstr(win, y, x, "Player ");
	waddch(win, champ.id + '0');
	waddstr(win, "\t: ");
	wattron(win, COLOR_PAIR(champ.id));
	waddstr(win, champ.name);
	wattroff(win, COLOR_PAIR(champ.id));
	mvwaddstr(win, y + 2, x, "Last Live\t: ");
	info = ft_itoa(champ.last_live);
	wattron(win, COLOR_PAIR(champ.id));
	waddstr(win, info);
	wattroff(win, COLOR_PAIR(champ.id));
	free(info);
	mvwaddstr(win, y + 3, x, "Current Lives\t: ");
	info = ft_itoa(champ.lives);
	wattron(win, COLOR_PAIR(champ.id));
	waddstr(win, info);
	wattroff(win, COLOR_PAIR(champ.id));
	free(info);
}

void	reset_champ_lives(t_champ *champs, int champ_count)
{
	int i;

	i = 0;
	while (i < champ_count)
	{
		champs[i].lives = 0;
		i++;
	}
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
