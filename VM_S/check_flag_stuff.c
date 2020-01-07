/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_flag_stuff.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/18 15:31:05 by awehlbur       #+#    #+#                */
/*   Updated: 2020/01/07 14:44:25 by awehlbur      ########   odam.nl         */
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
				vm->champs[vm->champ_nb].id = temp;
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
				vm->champs[vm->champ_nb].id = vm->tab[i];
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

void		check_valid_input(char **argv, int argc)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-' || ft_validate_format("%d", argv[i]) || ft_strstr(argv[i], ".cor"))
			i++;
		else
			ft_error("that is not a valid input");
	}
}

void		retrieve_flags(t_vm *vm, int argc, char **argv)
{
	int		i;

	i = 0;
	set_tab(vm);
	check_valid_input(argv, argc);
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == 'n')
			{
			if ((i + 2) >= argc)
				ft_error("Invalid flag");
			if (argv[i][2] != '\0')
				ft_error("Invalid -n flag");
			if (ft_validate_format("%d", argv[i + 1]) != 1)
				ft_error("Please enter the number the champion should be!");
			if (vm->champion_count < ft_atoi(argv[i + 1]))
				ft_error("That number is bigger than there are positions...");
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