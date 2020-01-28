/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_flag_stuff_helper.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 14:54:16 by awehlbur       #+#    #+#                */
/*   Updated: 2020/01/28 15:47:20 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			parse_number_helper(int i, t_vm *vm)
{
	while (i < vm->champion_count)
	{
		if ((vm->tab[i] % 10) != 0)
		{
			vm->champs[vm->champ_nb].id = vm->tab[i];
			vm->tab[i] *= 10;
			return (1);
		}
		i++;
	}
	return (0);
}

void		retreive_flags_helper(int argc, char **argv, int i, t_vm *vm)
{
	if ((i + 2) >= argc)
		ft_error("Invalid flag");
	if (ft_validate_format("%d", argv[i + 1]) != 1)
		ft_error("Please enter the number the champion should be!");
	if (vm->champion_count < ft_atoi(argv[i + 1]))
		ft_error("That number is bigger than there are positions...");
	if (ft_atoi(argv[i + 1]) < 1)
		ft_error("Size matters... it's too small");
	if (ft_strstr(argv[i + 2], ".cor"))
	{
		parse_number(vm, argv[i + 1]);
		read_file(vm, argv[i + 2], &vm->champs[vm->champ_nb]);
	}
	else
		ft_error("Number does not belong to a champion");
}
