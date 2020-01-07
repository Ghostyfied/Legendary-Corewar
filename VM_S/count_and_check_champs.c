/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_and_check_champs.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 16:00:54 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/07 16:01:28 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

static void		find_cor(t_vm *vm, char **string)
{
	int		i;

	i = 0;
	while (string[i])
	{
		if (ft_strcmp(string[i], "cor") == 0)
		{
			vm->champion_count++;
			return ;
		}
		i++;
	}
}

/*
** Count champions and split the string on spaces,
** then look for .cor extension to count
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
	if (vm->champion_count > MAX_PLAYERS)
		ft_error("too many champs omegalul");
	if (!vm->champion_count)
		ft_error("no players please put some in");
	vm->champs = (t_champ*)ft_memalloc(sizeof(t_champ) * vm->champion_count);
	vm->champ_position = MEM_SIZE / vm->champion_count;
}
