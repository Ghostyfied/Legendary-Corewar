#include "vm.h"

void	get_xy(int index, int *x, int *y)
{
	*y = (index / 64) + 1;
	*x = ((index % 64) * 3) + 1;
}

void	visualizer(t_vm *vm, WINDOW *win)
{
	int i;
	int j;
	int x;
	int y;
	int code;

	i = 0;
	start_color();
	while (i < vm->champion_count)
	{
		j = 0;
		code = CHAMPS[i].starting_pos;
		while (j < CHAMPS[i].code_size)
		{
			get_xy(code, &x, &y);
			wmove(win, y, x);
			waddch(win, ' ');
			init_pair(i + 1, vm->colours[i], COLOR_BLACK);
			wattron(win, COLOR_PAIR(i + 1));
			waddstr(win, get_hex(ARENA[code], 1));
			wattroff(win, COLOR_PAIR(i + 1));
			code++;
			j++;
		}
		i++;
	}
}