/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 13:28:02 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/17 13:35:22 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dis.h"

void		free_champ(t_champ *champ)
{
	t_operation *tmp;

	while (champ->operations)
	{
		tmp = champ->operations;
		champ->operations = champ->operations->next;
		free(tmp->args);
		free(tmp);
	}
	free(champ->name);
	free(champ->comment);
	free(champ);
	champ = NULL;
}
