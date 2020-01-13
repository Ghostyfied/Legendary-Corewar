#include "vm.h"

void	get_xy(int index, int *y, int *x)
{
	*y = (index / 64) + 1;
	*x = ((index % 64) * 3) + 1;
}

void	highlight_cursor(t_vm *vm, int prev, int pos, int attr)
{
	int		y;
	int		x;
	char	*hex;

	if (prev >= 0)
	{
		hex = get_hex(ARENA[prev], 1);
		get_xy(prev, &y, &x);
		wmove(VISUAL->arena_win, y, x + 1);
		wattron(VISUAL->arena_win, COLOR_PAIR(VISUAL->carena[prev]));
		waddstr(VISUAL->arena_win, hex);
		wattroff(VISUAL->arena_win, COLOR_PAIR(VISUAL->carena[prev]));
		free(hex);
	}
	get_xy(pos, &y, &x);
	mvwchgat(VISUAL->arena_win, y, x + 1, 2, attr, 0, NULL);
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
		wmove(VISUAL->arena_win, y, x);
		waddch(VISUAL->arena_win, ' ');
		hex = get_hex(ARENA[code], 1);
		wattron(VISUAL->arena_win, COLOR_PAIR(colour));
		waddstr(VISUAL->arena_win, hex);
		wattroff(VISUAL->arena_win, COLOR_PAIR(colour));
		free(hex);
		i++;
	}
}