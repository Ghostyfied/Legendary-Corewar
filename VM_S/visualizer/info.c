/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   info.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 16:39:15 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/17 15:33:27 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			paused(WINDOW *win)
{
	mvwaddstr(win, 5, 25, "PAUSED ");
	curs_set(0);
	wrefresh(win);
	while (getch() != ' ')
		;
}

void			champ_info(t_champ champ, int y, int x, WINDOW *win)
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
	waddstr(win, "          ");
	free(info);
}

void			reset_champ_lives(t_champ *champs, int champ_count)
{
	int i;

	i = 0;
	while (i < champ_count)
	{
		champs[i].lives = 0;
		i++;
	}
}

static	void	put_info(t_vm *vm, WINDOW *win)
{
	char	*info;

	mvwaddstr(win, 10, 10, "Cycles\t: ");
	info = ft_itoa(GAME->cycles_counter);
	waddstr(win, info);
	free(info);
	mvwaddstr(win, 12, 10, "Check at\t: ");
	info = ft_itoa(GAME->check_counter);
	waddstr(win, info);
	free(info);
	mvwaddstr(win, 13, 10, "Check every\t: ");
	info = ft_itoa(GAME->cycles_to_die);
	waddstr(win, info);
	waddstr(win, "       ");
	free(info);
	mvwaddstr(win, 15, 10, "Cursors\t: ");
	info = ft_itoa(GAME->cursors_count);
	waddstr(win, info);
	free(info);
	waddstr(win, "          ");
}

void			info_vis(t_vm *vm, WINDOW *win)
{
	int i;
	int y;

	wattron(win, A_BOLD);
	mvwaddstr(win, 4, 25, "COREWAR");
	wattroff(win, A_BOLD);
	mvwaddstr(win, 5, 25, "RUNNING");
	put_info(vm, win);
	i = 0;
	y = 20;
	while (i < vm->champion_count)
	{
		champ_info(CHAMPS[i], y, 10, win);
		y += 5;
		i++;
	}
	if (!CURSORS)
	{
		mvwaddstr(win, y + 15, 15, "*** WINNER : ");
		wattron(win, COLOR_PAIR(GAME->winner));
		waddstr(win, CHAMPS[GAME->winner - 1].name);
		wattroff(win, COLOR_PAIR(GAME->winner));
		waddstr(win, " ***");
	}
}
