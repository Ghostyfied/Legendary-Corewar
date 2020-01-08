/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assign_positions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/18 15:31:12 by awehlbur       #+#    #+#                */
/*   Updated: 2020/01/08 17:39:04 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void					check_champion_position(t_champ *champs, int champ_count)
{
	t_champ		temp_champ;
	int			i;

	i = 0;
	while (i < (champ_count - 1))
	{
		if (champs[i].id > champs[i + 1].id)
		{
			temp_champ = champs[i];
			champs[i] = champs[i + 1];
			champs[i + 1] = temp_champ;
		}
		i++;
	}
}
