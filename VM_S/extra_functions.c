/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 15:59:07 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/17 15:29:59 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Check whether the argument after -n is a number
*/

int		ft_is_a_number(char *str)
{
	size_t	i;

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
