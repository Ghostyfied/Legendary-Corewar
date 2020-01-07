/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 16:08:01 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/07 16:32:00 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dis.h"

/*
** Read file, put everything in content. set number of champs higher,
** set filename, set prog_size, send to champion checker.
** Copies the champions code into the correct position in the arena.
*/

void		read_file(t_champ *champ, char *file)
{
	int		fd;
	t_byte	*code;
	int		size;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error(strerror(errno));
	size = lseek(fd, 0, SEEK_END) - CODE_OFFSET;
	lseek(fd, 0, SEEK_SET);
	check_magic_header(fd);
	champ->name = get_name(fd);
	skip_bytes(fd, 4);
	champ->code_size = get_code_size(fd);
	if (size != champ->code_size || champ->code_size > CHAMP_MAX_SIZE)
		ft_error("Code size error");
	champ->comment = get_comment(fd);
	skip_bytes(fd, 4);
	decode_code(fd, champ);
	close(fd);
}
