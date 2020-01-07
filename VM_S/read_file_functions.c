/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file_functions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 15:48:21 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/07 15:50:02 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	check_magic_header(int fd)
{
	int mh;

	read(fd, &mh, 4);
	mh = swap_32(mh);
	if (mh != COREWAR_EXEC_MAGIC)
		ft_error("Magic Header error");
}

char	*get_comment(int fd)
{
	char	*comment;

	comment = ft_strnew(COMMENT_LENGTH);
	read(fd, comment, COMMENT_LENGTH);
	return (comment);
}

char	*get_name(int fd)
{
	char	*name;

	name = ft_strnew(PROG_NAME_LENGTH);
	read(fd, name, PROG_NAME_LENGTH);
	return (name);
}

int		get_code_size(int fd)
{
	int size;

	read(fd, &size, 4);
	size = swap_32(size);
	return (size);
}

void	skip_bytes(int fd, int amount)
{
	t_byte byte;

	while (amount > 0)
	{
		read(fd, &byte, 1);
		amount--;
	}
}
