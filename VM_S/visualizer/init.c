#include "vm.h"

void	init_vis(t_vm *vm)
{
	WINDOW *arena_win;
	WINDOW *info_win;
	int c;
	int i;
	int j;

	initscr();
	start_color();
	init_pair(1, PLAYER1_C, COLOR_BLACK);
	init_pair(2, PLAYER2_C, COLOR_BLACK);
	init_pair(3, PLAYER3_C, COLOR_BLACK);
	init_pair(4, PLAYER4_C, COLOR_BLACK);
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
		j++;
	}
	visualizer(vm, arena_win);
	info_vis(vm, info_win);
	wrefresh(arena_win);
	wrefresh(info_win);

	c = getch();
	endwin();
}