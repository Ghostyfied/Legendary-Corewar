/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compile.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:35:35 by awehlbur       #+#    #+#                */
/*   Updated: 2019/12/04 18:17:28 by rvan-ket      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Read complete file at once by using lseek and putting it in buffer.
*/
char			*ft_read_file(char *filename)
{
	int			fd;
	char		*buff;
	size_t		size;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_error("Can not read file\n");
	size = lseek(fd, 0, SEEK_END);	/* Set read pointer to the end of the file so return value is amount of bytes we need to read for the whole file*/
	if ((size < 1) || !(buff = ft_memalloc(size + 1)))
		ft_error("NO VALID FILE");
	lseek(fd, 0, SEEK_SET);	/* Set read pointer to beggining of the file */
	read(fd, buff, size); /* read whole file at once */
	close(fd);
	return (buff);
}