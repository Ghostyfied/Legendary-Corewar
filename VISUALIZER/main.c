#include <ncurses.h>

#define INFO_H LINES
#define INFO_W 80
#define ARENA_H LINES 
#define ARENA_W (COLS - INFO_W)

// gcc -lncurses main.c ; ./a.out

int main(void)
{
	WINDOW *arena_win;
	WINDOW *info_win;
	int c;
	
	initscr();
	cbreak();
	arena_win = newwin(ARENA_H, ARENA_W, 0, 0);
	info_win = newwin(INFO_H, INFO_W, 0, ARENA_W + 1);
	refresh();
	box(arena_win, 0, 0);
	wrefresh(arena_win);
	box(info_win, 0, 0);
	wrefresh(info_win);
	c = getch();

	return (endwin());
}