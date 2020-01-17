/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_nc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 16:16:26 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/17 16:11:34 by rvan-ket      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	check_line(char *str, int len)
{
	int i;

	i = len;
	while (str[i] && str[i] != '"')
	{
		if (str[i] != ' ' && str[i] != '\t')
			ft_error("Error parsing name and comment");
		i++;
	}
	i++;
	while (str[i] && str[i] != '"')
		i++;
	i++;
	while (str[i])
	{
		if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR)
			return ;
		if (str[i] != ' ' && str[i] != '\t')
			ft_error("Error parsing name and comment");
		i++;
	}
}

static char	*get_other_lines(char **champion, char *str, int *i, int j)
{
	while (champion[j])
	{
		j++;
		if (!champion[j])
			ft_error("Error parsing name and comment");
		str = ft_strjoinfree(str, ft_strdup("\n"));
		if (ft_strchr(champion[j], '"'))
		{
			str = ft_strjoinfree(str, ft_strsub(champion[j],
			0, ft_strchr(champion[j], '"') - champion[j]));
			checkafternewline(champion[j], chr_idx(champion[j], '"'));
			*i = j;
			return (str);
		}
		else
			str = ft_strjoin(str, champion[j]);
	}
	ft_error("Error parsing name and comment");
	return (str);
}


static char	*get_str(char **champion, int *i, int j, int len)
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

int			is_empty(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR)
			return (1);
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int			get_name_comm(char **champion, t_asm **asm_info)
{
	int		i;

	i = 0;
	(*asm_info)->name = NULL;
	(*asm_info)->comment = NULL;
	while (champion[i])
	{
		if (!ft_strncmp(".name", champion[i], 5))
			(*asm_info)->name = get_str(champion, &i, i, 5);
		else if (!ft_strncmp(".comment", champion[i], 8))
			(*asm_info)->comment = get_str(champion, &i, i, 8);
		else if (*champion[i] != '\n')
			ft_error("Error parsing name and comment");
		if ((*asm_info)->name && (*asm_info)->comment)
			break ;
		i++;
	}
	i++;
	while (champion[i] && is_empty(champion[i]))
		i++;
	if (!champion[i])
		ft_error("No champion code located");
	return (i);
}
