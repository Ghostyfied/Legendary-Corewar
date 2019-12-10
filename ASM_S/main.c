/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 16:06:32 by fhignett       #+#    #+#                */
/*   Updated: 2019/12/10 16:15:22 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	new_file_ext = ft_strnew(end - file + 2);
	ft_strncpy(new_file_ext, file, end - file + 1);
	ft_strncpy(ft_strrchr(new_file_ext, '.') + 1, "cor", 3);
	return (new_file_ext);
}

int			calchex(char one, char two)
{
	int		i;
	int		j;
	char	*hex;

	hex = ft_strdup("0123456789abcdef");
	i = ft_strchr(hex, one) - hex;
	j = ft_strchr(hex, two) - hex;
	return (16 * i + j);
}

void		puthex(char *str, int fd)
{
	int i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		ft_putchar_fd(calchex(str[i], str[i + 1]), fd);
		i += 2;
	}
}

void		make_file(char **champion, char *new_filename, t_asm *asm_info)
{
	int				fd;
	t_operation		*op;
	char			*exec_size;
	unsigned char	byte;

	fd = open(new_filename, O_CREAT | O_RDWR, 0666);
	if (fd < 0)
		ft_error(strerror(errno));
	ft_printf("Writing output program to %s\n", new_filename);
	puthex("00ea83f3", fd);
	puthex(asm_info->name, fd);
	puthex("00000000", fd);
	exec_size = get_hex(asm_info->exec_code_size, 4);
	puthex(exec_size, fd);
	free(exec_size);
	puthex(asm_info->comment, fd);
	puthex("00000000", fd);
	op = asm_info->operations;
	while (op)
	{
		puthex(op->executable, fd);
		op = op->next;
	}
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
	make_file(champion, new_file_ext, asm_info);
	ft_chararrfree(&champion);
	return (0);
}
