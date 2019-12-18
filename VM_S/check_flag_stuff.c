/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_flag_stuff.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/18 15:31:05 by awehlbur       #+#    #+#                */
/*   Updated: 2019/12/18 17:57:33 by awehlbur      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		set_tab(t_vm *vm)
{
	int		i;

	i = 0;
	vm->tab = (int*)ft_memalloc(sizeof(int) * vm->champion_count);
	while (i < vm->champion_count)
	{
		vm->tab[i] = i + 1;
		i++;
	}
}

void		parse_number(t_vm *vm, char *num)
{
	int		i;
	int		temp;

	i = 0;
	temp = ft_atoi(num);
	if (temp != -1)
	{
		while (i < vm->champion_count)
		{
			if (temp == vm->tab[i])
			{
				vm->champs[vm->champ_nb].nb_set = temp;
				vm->tab[i] *= 10;
				return ;
			}
			else if ((temp * 10) == vm->tab[i])
				ft_error("that number is taken");
			i++;
		}
	}
	else if (temp == -1)
	{
		while (i < vm->champion_count)
		{
			if ((vm->tab[i] % 10) != 0)
			{
				vm->champs[vm->champ_nb].nb_set = vm->tab[i];
				vm->tab[i] *= 10;
				return ;
			}
			i++;
		}
	}
}

void		get_champions_noflag(t_vm *vm, int argc, char **argv)
{
	int		i;

	i = 0;
	while (i < argc)
	{
		if ((i < 3 && ft_strstr(argv[i], ".cor")) || (ft_strstr(argv[i], ".cor") && argv[i - 2][0] != '-' && argv[i - 2][1] != 'n'))
		{
			parse_number(vm, "-1");
			read_file(vm, argv[i], &vm->champs[vm->champ_nb]);
		}
		i++;
	}
}

void		retrieve_flags(t_vm *vm, int argc, char **argv)
{
	int		i;

	i = 0;
	set_tab(vm);
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == 'n' && argv[i][2] == '\0' && (i + 2) < argc)
		{
			// if (!ft_validate_format("%d", argv[i + 1]))
			// 	ft_error("-n flag without valid number");
			if (ft_strstr(argv[i + 2], ".cor"))
			{
				parse_number(vm, argv[i + 1]);
				read_file(vm, argv[i + 2], &vm->champs[vm->champ_nb]);
			}
			else
				ft_error("Number does not belong to a champion");
		}
		i++;
	}
	get_champions_noflag(vm, argc, argv);
	check_champion_position(vm);
}