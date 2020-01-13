#include "vm.h"

void	visualizer(t_vm *vm, WINDOW *win)
{
	int		i;
	int		j;
	int		x;
	int		y;
	int		code;
	char	*hex;

	i = 0;
	while (i < vm->champion_count)
	{
		j = 0;
		code = CHAMPS[i].starting_pos;
		while (j < CHAMPS[i].code_size)
		{
			VISUAL->carena[code] = i + 1;
			get_xy(code, &y, &x);
			wmove(win, y, x);
			waddch(win, ' ');
			hex = get_hex(ARENA[code], 1);
			wattron(win, COLOR_PAIR(i + 1));
			waddstr(win, hex);
			wattroff(win, COLOR_PAIR(i + 1));
			free(hex);
			code++;
			j++;
		}
		highlight_cursor(vm, -1, CHAMPS[i].starting_pos, ATTR);
		i++;
	}
}