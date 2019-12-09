#include "asm.h"

int			ft_free_all(int	l)
{
	return (l);
}

char		*ft_check_filename(char *file)
{
	char	*end;
	char	*new_file_ext;

	new_file_ext = NULL;
	end = ft_strrchr(file, '.');
	if (!end)
		return (NULL);
	if (ft_strcmp(end, ".s"))
		return (NULL);
	new_file_ext = ft_strnew(end - file  + 2);
	ft_strncpy(new_file_ext, file, end - file + 1);
	ft_strncpy(ft_strrchr(new_file_ext, '.') + 1, "cor", 3);
	return (new_file_ext);
}

void	make_file(char **champion, char *new_filename)
{
	int fd;

	fd = open(new_filename, O_CREAT | O_RDWR, 0666);
	ft_putstr_fd("00ea 83f3 ", fd);
	

}

int			main(int argc, char **argv)
{
	int		res;
	char	*new_file_ext;
	char	**champion;
	t_asm	*asm_info;

	asm_info = malloc(sizeof(t_asm));
	if (argc < 2 || argc > 3)
		ft_error("Usage:");
	if (!(new_file_ext = ft_check_filename(argv[1])))
		ft_error("Can not read file");
	champion = ft_read_file(argv[1]);
	parse(champion, &asm_info);
	// make_file(champion, new_file_ext);
	ft_chararrfree(&champion);
	return (ft_free_all(0));
}