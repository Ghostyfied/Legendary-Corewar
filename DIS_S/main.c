#include "dis.h"

char		*ft_check_filename(char *file)
{
	char	*end;
	char	*new_file_ext;

	new_file_ext = NULL;
	end = ft_strrchr(file, '.');
	if (!end)
		return (NULL);
	if (ft_strcmp(end, ".cor"))
		return (NULL);
	new_file_ext = ft_strnew(end - file + 4);
	ft_strncpy(new_file_ext, file, end - file + 1);
	ft_strncpy(ft_strrchr(new_file_ext, '.') + 1, "s", 1);
	return (new_file_ext);
}

void		make_file(t_champ *champ, char *new_filename)
{
	int				fd;
	t_operation		*op;
	int				i;
	char			*arg;

	fd = open(new_filename, O_CREAT | O_RDWR, 0666);
	if (fd < 0)
		ft_error(strerror(errno));
	ft_printf("Writing output to %s\n", new_filename);
	dprintf(fd, ".name \"%s\"\n", champ->name);
	dprintf(fd, ".comment \"%s\"\n\n", champ->comment);
	op = champ->operations;
	while (op)
	{
		ft_putstr_fd(g_op_tab[op->op_code].name, fd);
		i = 0;
		while (i < op->nb_arg)
		{
			arg = op->args[i].type == T_REG ? "r" : op->args[i].type == T_DIR ? "\%" : "";
			dprintf(fd, " %s%d", arg, op->args[i].value);
			i++;
			if (i < op->nb_arg)
				ft_putchar_fd(',', fd);
		}
		ft_putendl_fd("", fd);
		op = op->next;
	}
	close(fd);
}

int			main(int argc, char **argv)
{
	char	*new_file_ext;
	char	*tmp;
	t_champ	*champ;

	if (argc < 2 || argc > 3)
		ft_error("Usage:");
	new_file_ext = ft_check_filename(argv[1]);
	if (!new_file_ext)
		ft_error("Can not read file");
	champ = MEM(t_champ);
	read_file(champ, argv[1]);
	tmp = new_file_ext;
	new_file_ext = ft_strjoin("dis_", new_file_ext);
	free(tmp);
	make_file(champ, new_file_ext);
	return (0);
}