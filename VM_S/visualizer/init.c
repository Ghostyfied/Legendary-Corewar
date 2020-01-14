/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 17:26:37 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/14 17:52:28 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			end_vis(t_vm *vm)
{
	paused(VISUAL->info_win);
	endwin();
}

void			refresh_windows(t_vm *vm, WINDOW *arena_win, WINDOW *info_win)
{
	info_vis(vm, info_win);
	curs_set(0);
	wrefresh(arena_win);
	wrefresh(info_win);
	usleep(SLEEP);
	if (wgetch(info_win) == ' ')
		paused(info_win);
}

void			init_colours(void)
{
	init_pair(1, PLAYER1_C, -1);
	init_pair(2, PLAYER2_C, -1);
	init_pair(3, PLAYER3_C, -1);
	init_pair(4, PLAYER4_C, -1);
}

static	void	init_arena(t_visualizer *vis)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (j < MEM_SIZE)
	{
		if (j % 64 == 0)
		{
			wmove(vis->arena_win, i, 1);
			i++;
		}
		waddstr(vis->arena_win, " 00");
		j++;
	}
}

void			init_vis(t_vm *vm)
{
	VISUAL = MEM(t_visualizer);
	initscr();
	start_color();
	use_default_colors();
	init_colours();
	cbreak();
	noecho();
	VISUAL->arena_win = newwin(ARENA_H, ARENA_W, 0, 0);
	VISUAL->info_win = newwin(INFO_H, INFO_W, 0, ARENA_W + 1);
	refresh();
	box(VISUAL->arena_win, 0, 0);
	box(VISUAL->info_win, 0, 0);
	init_arena(VISUAL);
	nodelay(VISUAL->info_win, true);
	visualizer(vm, VISUAL->arena_win);
	info_vis(vm, VISUAL->info_win);
	wrefresh(VISUAL->arena_win);
	paused(VISUAL->info_win);
}
