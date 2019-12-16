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

static char *get_name(fd)
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
**	Read file, put everything in content. set number of champs higher, set filename, set prog_size, send to champion checker.
*/

void		read_file(t_vm *vm, char *argv, t_champ *champ)
{
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		ft_error(strerror(errno));
	check_magic_header(fd);
	champ->name = get_name(fd);
	skip_bytes(fd, 4);
	champ->code_size = get_code_size(fd);
	champ->comment = get_comment(fd);
	skip_bytes(fd, 4);
	decode_code(fd, champ);
	close(fd);
	vm->nb++;
}
