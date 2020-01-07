/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/18 15:31:23 by awehlbur       #+#    #+#                */
/*   Updated: 2020/01/07 15:45:03 by awehlbur      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void check_magic_header(int fd)
{
	int mh;

	read(fd, &mh, 4);
	mh = swap_32(mh);
	if (mh != COREWAR_EXEC_MAGIC)
		ft_error("Magic Header error");
}

static char *get_comment(int fd)
{
	char	*comment;

	comment = ft_strnew(COMMENT_LENGTH);
	read(fd, comment, COMMENT_LENGTH);
	return (comment);
}

static char *get_name(int fd)
{
	char	*name;

	name = ft_strnew(PROG_NAME_LENGTH);
	read(fd, name, PROG_NAME_LENGTH);
	return (name);
}

static int	get_code_size(int fd)
{
	int size;

	read(fd, &size, 4);
	size = swap_32(size);
	return(size);
}

static void	skip_bytes(int fd, int amount)
{
	t_byte byte;

	while (amount > 0)
	{
		read(fd, &byte, 1);
		amount--;
	}
}

/*
** Read file, put everything in content. set number of champs higher, set filename, set prog_size, send to champion checker.
** Copies the champions code into the correct position in the arena.
*/

void		read_file(t_vm *vm, char *argv, t_champ *champ)
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
	{
		ft_printf("ERROR AT : %s\n", champ->name);
		ft_error("Code size error");
	}
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
