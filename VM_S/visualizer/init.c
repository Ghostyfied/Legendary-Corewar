#include "vm.h"

void	init_vis(t_vm *vm)
{
	WINDOW *arena_win;
	WINDOW *info_win;
	int c;
	int i;
	int j;

	vm->colours = (int[4]){PLAYER1_C, PLAYER2_C, PLAYER3_C, PLAYER4_C};
	initscr();
	cbreak();
	noecho();
	arena_win = newwin(ARENA_H, ARENA_W, 0, 0);
	info_win = newwin(INFO_H, INFO_W, 0, ARENA_W + 1);
	refresh();
	box(arena_win, 0, 0);
	box(info_win, 0, 0);
	i = 1;
	j = 0;
	while (j < MEM_SIZE)
	{
		if (j % 64 == 0)
		{
			wmove(arena_win, i, 1);
			i++;
		}
		waddstr(arena_win, " 00");
		// waddch(arena_win, ' ');
		// waddstr(arena_win, get_hex(ARENA[j], 1));
		j++;
	}
	visualizer(vm, arena_win);
	info_vis(vm, info_win);
	wrefresh(arena_win);
	wrefresh(info_win);
	
	c = getch();
	endwin();
}