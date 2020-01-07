<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 14:57:25 by awehlbur       #+#    #+#                */
/*   Updated: 2019/12/05 20:32:06 by awehlbur      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		vm_init_var(t_vm *vm)
{
	vm->player_number = 0;
}

int         main(int argc, char **argv)
{
	t_vm		vm;

	if (argc >= 2)
	{
		vm_init_var(&vm);
		if (validate_champions(argc, argv, &vm) == -1)
			ft_error("...");
	}
	else
		ft_error("Usage\n");
=======
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

/*
** Reminder/to do:
** • Add size to cursor->position after successful executed operation. And set cursor->moved to true
** • Everytime live is performed GAME->live_counter++. Will be reset during the cursor live check.
** • -d flag needs to be implemented, function already written.
** • When doing an operation, when copying a value into the arena, watch out for max index, for example if
**   	4 bytes are placed into the arena at index 4094, the last 2 bytes will be placed at index 0 and 1, right?
** • function get_arena_index() added, might be usefull. Gives you the correct index back after saying how many steps
**   	+ or - you want from current index.
** • -n3 and -n 3 flags both work, error?
** • ./corewar batman.cor buttman.s doesn't give an error?
** Visualizer if we have time/want to do it???
** Norminette ofcourse
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
	game(vm);
	free_vm(vm);
>>>>>>> master
    return (0);
}
