/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_champions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 16:29:28 by awehlbur       #+#    #+#                */
/*   Updated: 2020/01/10 14:21:03 by awehlbur      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_player	*ft_player_malloc(t_vm *vm, t_player *player)
{
	if (player == NULL)
	{
		player = ft_memalloc(sizeof(t_player));
		player->next = NULL;
	}
	else
	{
		while (player != NULL)
			player = player->next;
		player = ft_memalloc(sizeof(t_player));
		player->next = NULL;
	}
	vm->player_list_start = player;
	return (player);
}

int			validate_champions(int argc, char **argv, t_vm *vm, int i)
{
	int			j;
	int			num;
	int			temp;
	char		*c;

	i = 1;
	j = 0;
	num = -vm->player_number - 1;
	while (i < argc)
	{
		if ((c = ft_strstr(argv[i], ".cor")) && c != argv[i] && !c[4])
		{
			while (j < vm->player_number)
			{
				if (vm->players[j].num == num)
				{
					j++;
					temp = 1;
				}
				num -= temp ? 1 : 0;
				temp = 0;
			}
		}
	}
	return (1);
}
