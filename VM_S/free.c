/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 15:58:03 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/17 13:36:56 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			free_cursors(t_cursor *cursor)
{
	t_cursor *tmp;

	while (cursor)
	{
		tmp = cursor;
		cursor = cursor->next;
		free(tmp);
		tmp = NULL;
	}
}

static	void	free_champs(t_champ *champs, int champ_nb)
{
	int i;

	i = 0;
	while (i < champ_nb)
	{
		free(champs[i].name);
		free(champs[i].comment);
		i++;
	}
	free(champs);
}

void			free_vm(t_vm *vm)
{
	free_champs(CHAMPS, vm->champion_count);
	if (GAME)
	{
		free_cursors(CURSORS);
		free(GAME);
	}
	free(vm->tab);
	free(vm);
}
