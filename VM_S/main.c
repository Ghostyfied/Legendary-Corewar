/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 14:57:25 by awehlbur       #+#    #+#                */
<<<<<<< HEAD
/*   Updated: 2019/12/11 14:35:54 by rvan-ket      ########   odam.nl         */
=======
/*   Updated: 2019/12/12 21:37:06 by fhignett      ########   odam.nl         */
>>>>>>> 6ee5af4ff8a973b43ecf5e32792526e94856fbac
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_vm	*init_vm(void)
{
	t_vm *vm;

	vm = MEM(t_vm);
	vm->index = 1;
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
<<<<<<< HEAD
	vm_init(&vm);
	count_champions(&vm, argv);
	retrieve_flags(&vm, argc, argv);
	check_champion_position(&vm);
	start_cm(&vm);
	i = 0;
	i++;
=======
	vm = init_vm();
	count_champions(vm, argv);
	retrieve_flags(vm, argc, argv);
	check_champion_position(vm);
	print_champions(vm->champs, vm->count);
>>>>>>> 6ee5af4ff8a973b43ecf5e32792526e94856fbac
    return (0);
}
