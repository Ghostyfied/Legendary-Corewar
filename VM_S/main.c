#include "vm.h"

static t_vm	*init_vm(void)
{
	t_vm *vm;

	vm = MEM(t_vm);
	vm->arg_idx = 1;
	return (vm);
}

/*
**	control room for the program
*/

void		loop_cursors(t_vm *vm);

int         main(int argc, char **argv)
{
	t_vm	*vm;

	if (argc == 1)
		ft_error("Why you no put files in?");
	vm = init_vm();
	count_champions(vm, argv);
	retrieve_flags(vm, argc, argv);
	check_champion_position(vm);
	setup_game(vm);

	/* DEBUG */
	loop_cursors(vm);
	// int i = 0;

	// ft_printf("%d\n", ARENA[i]);
	// i++;
	// ft_printf("%d\n", ARENA[i]);
	// i++;
	// ft_printf("%d\n", ARENA[i]);
	// i++;
	// ft_printf("%d\n", get_2bytes(&ARENA[i]));
	// i++;
	// i++;
	// ft_printf("%d\n", get_2bytes(&ARENA[i]));
	// // GAME->cursors->position += 10;
	// print_cursor(GAME->cursors, false);
	/* DEBUG */
    return (0);
}
