/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 14:57:25 by awehlbur       #+#    #+#                */
/*   Updated: 2019/12/09 18:25:31 by rvan-ket      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
	retrieve_flags(&vm, argc, argv);
	check_champion_position(&vm);
	i = 0;
	i++;
    return (0);
}
