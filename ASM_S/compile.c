/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compile.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:35:35 by awehlbur       #+#    #+#                */
/*   Updated: 2019/12/04 17:05:01 by awehlbur      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_read_file(char *filename)
{
	int			fd;
	char		*buff;
	size_t		size;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_error("Can not read file\n");
	size = lseek(fd, 0, SEEK_END);
	if ((size < 1) || !(buff = ft_memalloc(size + 1)))
		return (NULL);
	lseek(fd, 0, SEEK_SET);
	read(fd, buff, size);
	ft_putstr(buff);
	close(fd);

	return (0);
}