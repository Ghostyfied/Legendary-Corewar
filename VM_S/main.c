/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 14:57:25 by awehlbur       #+#    #+#                */
/*   Updated: 2019/11/05 14:57:40 by awehlbur      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void		assign_nbr(t_vm *vm, int num)
{
	int		i;

	i = 0;
	while (i < vm->count)
	{
		if (vm->champs[i].nb_set == num)
			vm->champs[i].nb_set = 0;
		i++;
	}
	vm->champs[vm->index].nb_set = num;
}

/*
**	
*/
void		assign_champ_num(t_vm *vm, int argc, char **argv)
{
	vm->index++;
	if (vm->index < argc)
	{
		if ((ft_is_a_number(argv[vm->index]) == 1)
		{
			if (ft_atoi(argv[vm->index]) > 4 || ft_atoi(argv[vm->index]) < 0)
				ft_error("That position is not available");
			assign_nbr(vm, -ft_atoi(argv[vm->index]), vm->nb);
			vm->index++;
		}
		if (vm->index < argc)
			manage_file(vm, argv[vm->index], vm->nb);
		else
			ft_error("That wont work");
	}
	else
		ft_error("neither will that");
}

/*
**	check which flag it is, can add more ^^
*/
void		get_flag(t_vm *vm, int argc, char **argv)
{
	if (ft_strcmp(argv[vm->index], "-n") == 0)
		assign_champ_num(vm, argc, argv);
}

/*
**	Check for flags recursively and set nb.set to 0 if no -n flag is found
*/
void		retrieve_flags(t_vm *vm, int argc, char **argv)
{
	if (vm->index >= argc)
		return ;
	if (argv[vm->index][0] == '-')
		get_flag(vm, argc, argv);
	else
	{
		vm->champs[vm->nb].nb_set = 0;
		manage_file(vm, argv[vm->index], vm->nb);
	}
	vm->index++;
	retrieve_flags(vm, argc, argv);
}

/*
**	initialize values
*/
void		vm_init(t_vm *vm)
{
	vm->index = 1;
	vm->count = 0;
	vm->dump = 0;
	vm->nb = 0;
}

/*
**	control room for the program
*/
int         main(int argc, char **argv)
{
	int		i;
	t_vm	vm;

	if (argc == 1)
		ft_error("Why you no put files in?");
	vm_init(&vm);
	count_champions(&vm, argv);
	retrieve_flags(&vm, argc, **argv);
	check_champion_position(&vm);
	i = 0;
	i++;
    return (0);
}