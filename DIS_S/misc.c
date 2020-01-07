/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 16:33:16 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/07 16:34:11 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dis.h"

short	swap_16(short nb)
{
	short b1;
	short b2;

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
