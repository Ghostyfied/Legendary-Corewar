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
	ft_putendl("");
	int i = 0;
	ft_printf("%s\n", g_op_tab[ARENA[i++]].name);
	ft_printf("%d\n", ARENA[i++]);
	ft_printf("%d\n", ARENA[i++]);
	ft_printf("%d\n", get_2bytes(&ARENA[i]));
	i += 2;
	ft_printf("%d\n", get_2bytes(&ARENA[i]));
	i += 2;
	ft_printf("%s\n", g_op_tab[ARENA[i++]].name);
	ft_printf("%d\n", get_4bytes(&ARENA[i]));


    return (0);
}
