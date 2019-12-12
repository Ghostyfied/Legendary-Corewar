/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compile.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 16:04:31 by fhignett       #+#    #+#                */
/*   Updated: 2019/12/12 11:13:29 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	count_empty_lines(char **array, int *i)
{
	int		empty;
	char	*tmp;

	empty = 0;
	while (array[*i])
	{
		tmp = array[*i];
		array[*i] = strtrim(array[*i]);
		free(tmp);
		empty += !ft_strlen(array[*i]) ? 1 : 0;
		(*i)++;
	}
	return (empty);
}

/*
** Deletes all empty lines,
** and replaces all ' ' and '\t' with a single ' 'and trims all lines.
*/

char		**delete_empty_lines(char **old, int *idx)
{
	int		empty;
	int		i;
	int		j;
	char	**new;

	i = *idx;
	empty = count_empty_lines(old, &i);
	if (!empty)
		return (old);
	new = (char**)ft_memalloc(sizeof(char*) * ((i - empty - *idx) + 1));
	i = *idx;
	j = 0;
	while (old[i])
	{
		if (ft_strlen(old[i]))
		{
			new[j] = ft_strdup(old[i]);
			j++;
		}
		i++;
	}
	ft_chararrfree(&old);
	*idx = 0;
	return (new);
}

void		delete_comments(char **champion, char comment_char)
{
	int		i;
	char	*comment;
	char	*tmp;
	int		size;

	i = 0;
	while (champion[i])
	{
		comment = ft_strchr(champion[i], comment_char);
		if (comment)
		{
			tmp = champion[i];
			size = comment - champion[i];
			champion[i] = ft_strnew(size);
			ft_strncpy(champion[i], tmp, size);
			free(tmp);
		}
		i++;
	}
}

/*
**	Read complete file at once by using lseek and putting it in buffer.
*/

char		**ft_read_file(char *filename)
{
	int			fd;
	char		*buff;
	char		*tmp;
	size_t		size;
	char		**champion;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_error(strerror(errno));
	size = lseek(fd, 0, SEEK_END);
	if ((size < 1) || !(buff = ft_memalloc(size + 1)))
		ft_error("NO VALID FILE");
	lseek(fd, 0, SEEK_SET);
	read(fd, buff, size);
	close(fd);
	champion = ft_strsplit(buff, '\n');
	ft_strdel(&buff);
	return (champion);
}
