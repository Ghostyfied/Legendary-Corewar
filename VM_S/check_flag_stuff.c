

#include "vm.h"

/*
**	check which flag it is and go to parsing function, can add more ^^
*/
void		get_flag(t_vm *vm, int argc, char **argv)
{
	if (ft_strcmp(argv[vm->arg_idx], "-n") == 0)
		assign_champ_num(vm, argc, argv); /* Assign Champion number from the flag */
}

/*
**	Check for flags recursively and set nb.set to 0 if no -n flag is found. read_file if no flag is found, otherwise go into flagchecker
*/
void		retrieve_flags(t_vm *vm, int argc, char **argv)
{
	if (vm->arg_idx >= argc)
		return ;
	if (argv[vm->arg_idx][0] == '-')
		get_flag(vm, argc, argv);
	else
	{
		vm->champs[vm->champ_nb].nb_set = 0;
		read_file(vm, argv[vm->arg_idx], &vm->champs[vm->champ_nb]);
	}
	vm->arg_idx++;
	retrieve_flags(vm, argc, argv);
}