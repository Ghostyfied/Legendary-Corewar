/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/21 18:19:19 by tide-jon       #+#    #+#                */
/*   Updated: 2019/12/06 15:12:48 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int counter;

	if (!str)
		return (0);
	counter = 0;
	while (str[counter] != '\0')
		counter++;
	return (counter);
}
