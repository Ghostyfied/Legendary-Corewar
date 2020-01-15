/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 16:08:41 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/15 16:07:10 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	get_xy(int index, int *y, int *x)
{
	*y = (index / 64) + 1;
	*x = ((index % 64) * 3) + 1;
}

void	highlight_cursor(t_vm *vm, int prev, int pos)
{
	int		y;
	int		x;
	char	*hex;
	int		colour;

	if (prev >= 0)
	{
		colour = VISUAL->carena[prev];
		hex = get_hex(ARENA[prev], 1);
		get_xy(prev, &y, &x);
		wattron(VISUAL->arena_win, COLOR_PAIR(colour));
		mvwaddstr(VISUAL->arena_win, y, x + 1, hex);
		wattroff(VISUAL->arena_win, COLOR_PAIR(colour));
		free(hex);
	}
	if (pos >= 0)
	{
		colour = VISUAL->carena[pos] ? (VISUAL->carena[pos] + 4) : 9;
		hex = get_hex(ARENA[pos], 1);
		get_xy(pos, &y, &x);
		wattron(VISUAL->arena_win, COLOR_PAIR(colour));
		mvwaddstr(VISUAL->arena_win, y, x + 1, hex);
		wattroff(VISUAL->arena_win, COLOR_PAIR(colour));
		free(hex);
	}
}

void	update_arena(t_vm *vm, int pos, int colour)
{
	int		i;
	int		y;
	int		x;
	int		code;
	char	*hex;

	i = 0;
	while (i < 4)
	{
		code = get_arena_index(pos, i);
		get_xy(code, &y, &x);
		mvwaddch(VISUAL->arena_win, y, x, ' ');
		hex = get_hex(ARENA[code], 1);
		wattron(VISUAL->arena_win, COLOR_PAIR(colour));
		wattron(VISUAL->arena_win, A_BOLD);
		waddstr(VISUAL->arena_win, hex);
		wattroff(VISUAL->arena_win, A_BOLD);
		wattroff(VISUAL->arena_win, COLOR_PAIR(colour));
		VISUAL->carena[code] = colour;
		VISUAL->copied[code] = COPIED_CYCLES;
		free(hex);
		i++;
	}
}

void	update_copied(t_vm *vm)
{
	int		i;
	int		y;
	int		x;
	char	*hex;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (VISUAL->copied[i] == 1)
		{
			get_xy(i, &y, &x);
			mvwaddch(VISUAL->arena_win, y, x, ' ');
			hex = get_hex(ARENA[i], 1);
			wattron(VISUAL->arena_win, COLOR_PAIR(VISUAL->carena[i]));
			waddstr(VISUAL->arena_win, hex);
			wattroff(VISUAL->arena_win, COLOR_PAIR(VISUAL->carena[i]));
			free(hex);
		}
		if (VISUAL->copied[i] > 0)
			VISUAL->copied[i]--;
		i++;
	}
}
