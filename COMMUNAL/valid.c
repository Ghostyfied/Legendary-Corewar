/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 13:04:27 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/08 13:07:08 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "communal.h"

int		octal_valid(t_byte octal, int nb_arg)
{
	int shift;

	if (octal & 3)
		return (0);
	if (nb_arg == 3)
		return (1);
	shift = nb_arg * 2;
	if (((octal << shift) & 0xff))
		return (0);
	return (1);
}
