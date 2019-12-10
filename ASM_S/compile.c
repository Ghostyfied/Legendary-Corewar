/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compile.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 16:04:31 by fhignett       #+#    #+#                */
/*   Updated: 2019/12/10 16:05:19 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Read complete file at once by using lseek and putting it in buffer.
*/

char			**ft_read_file(char *filename)
{
	int			fd;
	char		*buff;
	char		*tmp;
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
	fd = 0;
	while (champion[fd])
	{
		tmp = champion[fd];
		champion[fd] = strtrim(champion[fd]);
		free(tmp);
		fd++;
	}
	ft_strdel(&buff);
	return (champion);
}
