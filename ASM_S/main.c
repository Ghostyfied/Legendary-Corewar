/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: awehlbur <awehlbur@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 13:42:40 by awehlbur       #+#    #+#                */
/*   Updated: 2019/12/04 15:30:04 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_free_all(int	l)
{
	return (l);
}

char		*ft_check_filename(char *file)
{
	char	*end;
	char	*new_file_ext;
	size_t	diff;

	new_file_ext = NULL;
	end = ft_strrchr(file, '.');
	if (!end)
		return (NULL);
	if (ft_strcmp(end, ".s"))
		return (NULL);
	diff = end - file;
	new_file_ext = ft_strnew(diff  + 4);
	ft_strncpy(new_file_ext, file, diff + 1);
	ft_strncpy(ft_strrchr(new_file_ext, '.') + 1, "cor", 3);
	return (new_file_ext);
}

int			main(int argc, char **argv)
{
	int		res;
	char	*new_file_ext;

	if (argc < 2 || argc > 3)
		ft_error("Usage:");
	if (!(new_file_ext = ft_check_filename(argv[1])))
		ft_error("Can not read file");
	if ((res = ft_compile(argv[1], new_file_ext)))
		return (ft_free_all(0));
	ft_putstr("Assembled output written to ");
	ft_putendl(new_file_ext);
	ft_strdel(&new_file_ext);
	return (ft_free_all(0));
}