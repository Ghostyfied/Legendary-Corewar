/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 15:53:57 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/15 17:03:06 by rvan-ket      ########   odam.nl         */
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

static void		ft_usage(char *name)
{
	ft_printf("Usage: %s [-v | -d n] [-n n] <file.cor> <...>\n", name);
	ft_putendl("\n\t-v\t: Visualization, takes priority over -d if both given");
	ft_putendl("\t-d n\t: Hex dump after n cycles");
	ft_putendl("\t-n n\t: Indicate which player (n) <file.cor> will be");
	exit(1);
}

int				main(int argc, char **argv)
{
	t_vm *vm;

	if (argc == 1)
		ft_usage(argv[0]);
	vm = init_vm();
	count_champions(vm, argv);
	retrieve_flags(vm, argc, argv);
	check_champion_position(CHAMPS, vm->champion_count);
	setup_game(vm);
	game(vm);
	free_vm(vm);
	return (0);
}
