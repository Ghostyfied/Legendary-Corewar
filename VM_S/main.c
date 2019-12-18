#include "vm.h"

static t_vm	*init_vm(void)
{
	t_vm *vm;

	vm = MEM(t_vm);
	vm->arg_idx = 1;
	vm->c_count = 0;
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
<<<<<<< HEAD
	check_champion_position(vm);
=======


	/* debugggingggg */
	int j = 0;
	int	i = 0;
	while (i < vm->champion_count)
	{
		// ft_putnbr(vm->tab[i]);
		ft_putstr(vm->champs[i].name);
		write(1, "\n", 1);
		i++;
	}
	// while (j < vm->champs[0].code_size)
	// {
	// 	ft_printf("%d\n", vm->arena[j]);
	// 	j++;
	// }
>>>>>>> b893685410470eb34019103f1f6efceaab0441b9
    return (0);
}
