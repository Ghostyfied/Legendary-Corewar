#include "vm.h"

void	get_xy(int index, int *y, int *x)
{
	*y = (index / 64) + 1;
	*x = ((index % 64) * 3) + 1;
}

void	highlight_cursor(t_vm *vm, t_cursor *c, int attr)
{
	int y;
	int x;

	get_xy(c->position, &y, &x);
	mvwchgat(VISUAL->arena_win, y, x + 1, 2, attr, 0, NULL);
}

void	update_arena(t_byte *arena, int pos, int amount)
{
	int y;
	int x;
	int i;

	i = 0;

	get_xy(pos, &y, &x);


}
