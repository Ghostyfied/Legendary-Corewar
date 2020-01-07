/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 15:59:07 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/07 16:00:05 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Check whether the argument after -n is a number
*/

int		ft_is_a_number(char *str)
{
	int		i;

	i = -1;
	if (str[0] == '-' && str[1])
		i++;
	while (i < ft_strlen(str))
	{
		if (ft_isdigit(str[i] == 0))
			return (0);
	}
	return (1);
}

short	swap_16(short nb)
{
	int b1;
	int b2;

	b1 = (nb & 0x00ff) << 8;
	b2 = (nb & 0xff00) >> 8;
	return (b1 | b2);
}

int		swap_32(int nb)
{
	int b1;
	int b2;
	int b3;
	int b4;

	b1 = (nb & 0x000000ff) << 24;
	b2 = (nb & 0x0000ff00) << 8;
	b3 = (nb & 0x00ff0000) >> 8;
	b4 = (nb & 0xff000000) >> 24;
	return (b1 | b2 | b3 | b4);
}
