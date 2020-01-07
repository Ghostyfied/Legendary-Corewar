/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assign_positions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/18 15:31:12 by awehlbur       #+#    #+#                */
/*   Updated: 2020/01/07 15:57:18 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		check_champion_position(t_vm *vm)
{
	t_champ		temp_champ;
	int			i;

	i = 0;
	while (i < vm->champion_count)
	{
		if (vm->champs[i].id > vm->champs[i + 1].id)
		{
			temp_champ = vm->champs[i];
			vm->champs[i] = vm->champs[i + 1];
			vm->champs[i + 1] = temp_champ;
		}
		i++;
	}
}
