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
    return (0);
}