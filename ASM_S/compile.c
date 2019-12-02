/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compile.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:35:35 by awehlbur       #+#    #+#                */
/*   Updated: 2019/11/05 17:34:47 by awehlbur      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_compile(char *filename, char *new_filename)
{
	int			fd;
	char		*buff;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_error("Can not read file\n");
	return (0);
}