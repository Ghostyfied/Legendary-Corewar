/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_and_check_champs.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/08 14:48:22 by anonymous      #+#    #+#                */
/*   Updated: 2019/12/08 14:48:22 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void			ft_arrdel(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int				ft_arrlen(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void			set_no_flag_number(t_vm *vm, int num, int nb)
{
	int		i;

	i = 0;
	while (i < vm->count)
	{
		if (vm->champs[i].nb_set == nb)
		{
			set_no_flag_number(vm, num, nb - 1);
			return ;
		}
		i++;
	}
	vm->champs[num].nb_set = nb;
}

static void		find_cor(t_vm *vm, char **string)
{
	int		i;

	i = 0;
	while (string[i])
	{
		if (ft_strcmp(string[i], "cor") == 0)
		{
			vm->count++;
			return ;
		}
		i++;
	}
}

/*
**	Count champions and split the string on spaces, then look for .cor extension to count
*/
void			count_champions(t_vm *vm, char **argv)
{
	int		i;
	char	**split;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] != '-')
		{
			split = ft_strsplit(argv[i], '.');
			if (ft_arrlen(split) > 1)
				find_cor(vm, split);
			ft_arrdel(split);
		}
		i++;
	}
	if (vm->count > 4)
		ft_error("too many champs omegalul");
	if (vm->count == 0)
		ft_error("no players please put some in");
	vm->champs = (t_champ*)malloc(sizeof(t_champ) * vm->count);
}

/*
**	Check if champs are in right order
*/
static void		arrange_champs_order(t_vm *vm)
{
	int		n;
	int		i;
	t_champ	champ;

	i = 0;
	while (i < vm->count)
	{
		n = 0;
		while (n < vm->count)
		{
			if (n + 1 < vm->count)
			{
				if (vm->champs[n].nb_set < vm->champs[n + 1].nb_set)
				{
					champ = vm->champs[n];
					vm->champs[n] = vm->champs[n + 1];
					vm->champs[n + 1] = champ;
				}
			}
			n++;
		}
		i++;
	}
}

void			check_champion_position(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->count)
	{
		if (vm->champs[i].nb_set == 0)
			set_no_flag_number(vm, i, -1);
		i++;
	}
	arrange_champs_order(vm);
}