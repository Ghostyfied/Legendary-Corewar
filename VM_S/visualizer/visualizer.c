/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   visualizer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 17:32:18 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/14 17:55:32 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	void	put_code(t_vm *vm, WINDOW *win, int i)
{
	int		j;
	int		x;
	int		y;
	int		code;
	char	*hex;

	j = 0;
	code = CHAMPS[i].starting_pos;
	wattron(win, COLOR_PAIR(i + 1));
	while (j < CHAMPS[i].code_size)
	{
		VISUAL->carena[code] = i + 1;
		get_xy(code, &y, &x);
		mvwaddch(win, y, x, ' ');
		hex = get_hex(ARENA[code], 1);
		waddstr(win, hex);
		free(hex);
		code++;
		j++;
	}
	wattroff(win, COLOR_PAIR(i + 1));
}

void			visualizer(t_vm *vm, WINDOW *win)
{
	int	i;

	i = 0;
	while (i < vm->champion_count)
	{
		put_code(vm, win, i);
		highlight_cursor(vm, -1, CHAMPS[i].starting_pos, ATTR);
		i++;
	}
}
