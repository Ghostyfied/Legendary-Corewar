/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trim.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 16:17:15 by fhignett       #+#    #+#                */
/*   Updated: 2019/12/10 16:22:51 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	iswspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

static int	count_len(char *s)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (!iswspace(s[i]))
		{
			len++;
			i++;
		}
		else if (iswspace(s[i]))
		{
			while (iswspace(s[i]))
				i++;
			if (s[i])
				len++;
		}
	}
	return (len);
}

static char	*replace_wspaces(char *trim, char *s, int *j, int *i)
{
	trim[*j] = ' ';
	(*j)++;
	while (iswspace(s[*i]))
		(*i)++;
	return (trim);
}

static char	*copy_str(char *trim, char *s, int *j, int *i)
{
	trim[*j] = s[*i];
	(*i)++;
	(*j)++;
	return (trim);
}

/*
** Trims a string of all tabs and spaces at beginning and end of string.
** Replaces all tabs and spaces for one space and returns this new string.
*/

char		*strtrim(char *s)
{
	int		j;
	int		i;
	int		len;
	char	*trim;

	i = 0;
	if (!s)
		return (NULL);
	while (iswspace(s[i]))
		i++;
	if (!s[i])
		return (ft_strdup(""));
	len = count_len(&s[i]);
	trim = (char*)ft_memalloc(sizeof(char) * (len + 1));
	j = 0;
	while (s[i] && j < len)
	{
		if (iswspace(s[i]))
			trim = replace_wspaces(trim, s, &j, &i);
		else
			trim = copy_str(trim, s, &j, &i);
	}
	return (trim);
}
