/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 16:06:32 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/17 16:09:27 by rvan-ket      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*ft_check_filename(char *file)
{
	char	*end;
	char	*new_file_ext;

	new_file_ext = NULL;
	end = ft_strrchr(file, '.');
	if (!end)
		return (NULL);
	if (ft_strcmp(end, ".s"))
		return (NULL);
	new_file_ext = ft_strnew(ft_strlen(file) + 2);
	ft_strncpy(new_file_ext, file, ft_strlen(file) - 1);
	ft_strncpy(ft_strrchr(new_file_ext, '.') + 1, "cor", 3);
	return (new_file_ext);
}

static int	calchex(char one, char two)
{
	int		i;
	int		j;
	char	*hex;

	hex = ft_strdup("0123456789abcdef");
	i = ft_strchr(hex, one) - hex;
	j = ft_strchr(hex, two) - hex;
	free(hex);
	return (16 * i + j);
}

static void	puthex(char *str, int fd)
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

static void	make_file(char **champion, char *new_filename, t_asm *asm_info)
{
	int				fd;
	t_operation		*op;
	char			*exec_size;
	unsigned char	byte;

	fd = open(new_filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
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
	close(fd);
	free(new_filename);
}

int			main(int argc, char **argv)
{
	int		res;
	char	*new_file_ext;
	char	**champion;
	t_asm	*asm_info;

	asm_info = MEM(t_asm);
	if (argc < 2 || argc >= 3)
		ft_usage(argv[0]);
	new_file_ext = ft_check_filename(argv[1]);
	if (!new_file_ext)
		ft_error("Can not read file");
	champion = ft_read_file(argv[1]);
	parse(champion, &asm_info);
	make_file(champion, new_file_ext, asm_info);
	free_asm(asm_info);
	return (0);
}
