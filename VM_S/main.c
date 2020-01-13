/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 15:53:57 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/13 17:22:17 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	t_vm	*init_vm(void)
{
	t_vm *vm;

	vm = MEM(t_vm);
	vm->arg_idx = 1;
	vm->dump = -1;
	return (vm);
}

/*
**	control room for the program
*/

/*
** Reminder/to do:
** - -d(ump) /-v(isual) flag needs to be implemented, function already written.
** - ./corewar batman.cor buttman.s doesn't give an error?
** Norminette ofcourse
*/

int				main(int argc, char **argv)
{
	t_vm *vm;

	if (argc == 1)
		ft_error("Why you no put files in?");
	vm = init_vm();
	count_champions(vm, argv);
	retrieve_flags(vm, argc, argv);
	check_champion_position(CHAMPS, vm->champion_count);
	setup_game(vm);
	game(vm);
	free_vm(vm);
	return (0);
}
