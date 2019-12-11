#include "vm.h"

void	print_byte(const void *byte, size_t size)
{
	int					idx;
	size_t				i;
	const unsigned char	*b;

	i = 0;
	b = (const unsigned char *)byte;
	while (i < size)
	{
		idx = 7;
		while (idx >= 0)
		{
			if (idx == 3)
				write(1, " ", 1);
			if ((b[i] & (1 << idx)) != 0)
				write(1, "1", 1);
			else
				write(1, "0", 1);
			idx--;
		}
		ft_putendl("");
		i++;
	}
}

short swap_16(short nb)
{
	short b1;
	short b2;

	b1 = (nb & 0x00ff) << 8;
	b2 = (nb & 0xff00) >> 8;
	return (b1 | b2);
}

int	swap_32(int nb)
{
	int b1;
	int b2;
	int b3;
	int b4;

	b1 = (nb & 0x000000ff) << 24;
	b2 = (nb & 0x0000ff00) << 8;
	b3 = (nb & 0x00ff0000) >> 8;
	b4 = (nb & 0xff000000) >> 24;
	return (b1 | b2 | b3 | b4);
}

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

static t_byte *get_code(int fd, int size)
{
	t_byte *code;

	code = (t_byte*)ft_strnew(size);
	read(fd, code, size);
	return (code);
}

/*
**	Read file, put everything in content. set number of champs higher, set filename, set prog_size, send to champion checker.
*/

void		read_file(t_vm *vm, char *argv, int num)
{
	int		fd;
	char	*name;
	char	*comment;
	int		code_size;
	t_byte	*code;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		ft_error(strerror(errno));
	check_magic_header(fd);
	name = get_name(fd);
	skip_bytes(fd, 4);
	code_size = get_code_size(fd);
	comment = get_comment(fd);
	skip_bytes(fd, 4);
	code = get_code(fd, code_size);
	close(fd);
	vm->nb++;
}
