/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compile.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:35:35 by awehlbur       #+#    #+#                */
/*   Updated: 2020/01/15 13:37:25 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			**ft_read_file(char *filename)
{
	int			fd;
	char		*buff;
	size_t		size;
	char		**champion;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error(strerror(errno));
	size = lseek(fd, 0, SEEK_END);
	buff = ft_memalloc(size + 1);
	if ((size < 1) || !buff)
		ft_error("NO VALID FILE");
	lseek(fd, 0, SEEK_SET);
	read(fd, buff, size);
	close(fd);
	champion = ft_strsplit(buff, '\n');
	ft_strdel(&buff);
	return (champion);
}
