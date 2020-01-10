/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compile.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:35:35 by awehlbur       #+#    #+#                */
/*   Updated: 2020/01/10 14:13:47 by awehlbur      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			**ft_read_file(char *filename)
{
	int			fd;
	char		*buff;
	size_t		size;
	char		**champion;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_error(strerror(errno));
	size = lseek(fd, 0, SEEK_END);
	if ((size < 1) || !(buff = ft_memalloc(size + 1)))
		ft_error("NO VALID FILE");
	lseek(fd, 0, SEEK_SET);
	read(fd, buff, size);
	close(fd);
	champion = ft_strsplit(buff, '\n');
	ft_strdel(&buff);
	return (champion);
}
