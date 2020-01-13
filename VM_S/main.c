/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 15:53:57 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/13 11:10:33 by fhignett      ########   odam.nl         */
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
** - Basic operations
** - Add size to cursor->position after successful executed operation
** 		and set cursor->moved to true
** - Everytime live is performed GAME->live_counter++.
**		Will be reset during the cursor live check.
** - -d flag needs to be implemented, function already written.
** - When doing an operation, when copying a value into the arena,
**		watch out for max index, for example if 4 bytes are placed into
**		the arena at index 4094, the last 2 bytes will be placed at index
**		0 and 1, right?
** - function get_arena_index() added, might be usefull. Gives you the correct
**		index back after saying how many steps
**   	+ or - you want from current index.
** - ./corewar batman.cor buttman.s doesn't give an error?
** Visualizer if we have time/want to do it???
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
