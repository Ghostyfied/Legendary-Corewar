/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/27 14:41:55 by tide-jon       #+#    #+#                */
/*   Updated: 2020/01/08 18:08:55 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*fresh;

	fresh = (char*)malloc(size * sizeof(char) + 1);
	if (fresh == NULL)
		return (NULL);
	ft_bzero(fresh, size + 1);
	return (fresh);
}
