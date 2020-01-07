/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 15:42:23 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/07 16:45:38 by awehlbur      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Read file, put everything in content. set number of champs higher,
** set filename, set prog_size, send to champion checker.
** Copies the champions code into the correct position in the arena.
*/

void			read_file(t_vm *vm, char *argv, t_champ *champ)
{
	int		fd;
	t_byte	*code;
	int		size;

	fd = open(argv, O_RDONLY);
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
	code = (t_byte*)ft_memalloc(sizeof(t_byte) * champ->code_size);
	read(fd, code, champ->code_size);
	champ->starting_pos = vm->champ_position * (champ->id - 1);
	ft_memcpy(&ARENA[champ->starting_pos], code, champ->code_size);
	close(fd);
	free(code);
	vm->champ_nb++;
}
