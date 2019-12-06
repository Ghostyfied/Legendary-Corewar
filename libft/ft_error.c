/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/16 19:06:48 by tide-jon       #+#    #+#                */
/*   Updated: 2019/12/06 16:16:04 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_error(char *str)
{
	ft_putendl(str);
	exit(1);
}
