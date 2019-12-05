/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_nc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-ket <rvan-ket@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 16:04:05 by rvan-ket       #+#    #+#                */
/*   Updated: 2019/12/05 19:17:42 by rvan-ket      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*get_other_lines(char **champion, char *str, int *i, int j)
{
	while (champion[j])
	{
		j++;
		if (ft_strchr(champion[j], '"'))
		{
			str = ft_strjoinfree(str, ft_strsub(champion[j],
			0, ft_strchr(champion[j], '"') - champion[j]));
			*i = j;
			return (str);
		}
		else
			str = ft_strjoinfree(str, champion[j]);
	}
	printf("ERROR ? \n parse_nc.c <-");
	return (str);
}

void	check_line(char *str, int len)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (str[i] && i < len)
		i++;
	while (str[i] && str[i] != '"')
	{
		if (str[i] != ' ' && str[i] != '\t')
			ft_error("Name or comment wrong format boi");
		i++;
	}
	i++;
	while (str[i] && str[i] != '"')
		i++;
	i++;
	while (str[i])
	{
		if (str[i] == COMMENT_CHAR)
			return ;
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			ft_error("Name or comment wrong format boii");
		i++;
	}
}

char	*get_str(char **champion, int *i, int j, int len)
{
	char *ptr;
	char *ptr2;
	char *str;

	ptr = ft_strchr(champion[j], '"');
	ptr2 = ft_strchr(ptr + 1, '"');
	if (ptr2 == NULL)
	{
		str = ft_strsub(champion[j], ptr - champion[j] + 1,
		ft_strchr(champion[j], '\0') - champion[j]);
		str = get_other_lines(champion, str, &j, j);
	}
	else
	{
		check_line(champion[j], len);
		str = ft_strsub(champion[j], ptr - champion[j] + 1, ptr2 - ptr - 1);
	}
	*i = j;
	return (str);
}

int	get_name_comm(char **champion)
{
	int		i;
	char	*name;
	char	*comment;

	i = 0;
	name = NULL;
	comment = NULL;
	while (champion[i])
	{
		if (!ft_strncmp(".name", champion[i], 5))
			name = get_str(champion, &i, i, 5);
		else if (!ft_strncmp(".comment", champion[i], 8))
			comment = get_str(champion, &i, i, 8);
		else if (*champion[i] != '\n')
			ft_error("foute naam of comment brobro");
		if (name && comment)
			break ;
		i++;
	}
	ft_putendl(name);
	ft_putendl(comment);
	return (i);
}
