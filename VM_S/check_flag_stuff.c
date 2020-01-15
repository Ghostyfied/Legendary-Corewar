/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_flag_stuff.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/18 15:31:05 by awehlbur       #+#    #+#                */
/*   Updated: 2020/01/15 13:53:10 by fhignett      ########   odam.nl         */
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
		if (parse_number_helper(i, vm) == 1)
			return ;
	}
}

void		get_champions_noflag(t_vm *vm, int argc, char **argv)
{
	int		i;

	i = 0;
	while (i < argc)
	{
		if ((i < 3 && ft_strstr(argv[i], ".cor")) ||
		(ft_strstr(argv[i], ".cor") && !ft_strequ(argv[i - 2], "-n")))
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
		if (ft_strequ(argv[i], "-n") || ft_strequ(argv[i], "-d") \
			|| ft_strequ(argv[i], "-v") \
			|| (ft_validate_format("%d", argv[i]) && \
				ft_strequ(argv[i - 1], "-n")) \
			|| (ft_validate_format("%d", argv[i]) && \
				ft_strequ(argv[i - 1], "-d")) \
			|| ft_strstr(argv[i], ".cor"))
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
		if (ft_strequ(argv[i], "-d") && (i + 2) < argc)
		{
			if (!ft_validate_format("%d", argv[i + 1]))
				ft_error("That is not a valid number for the hexdump");
			vm->dump = ft_atoi(argv[i + 1]);
		}
		else if (ft_strequ(argv[i], "-n"))
			retreive_flags_helper(argc, argv, i, vm);
		else if (ft_strequ(argv[i], "-v"))
			vm->vflag = true;
		i++;
	}
	get_champions_noflag(vm, argc, argv);
}
