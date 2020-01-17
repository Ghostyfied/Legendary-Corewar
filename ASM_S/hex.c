/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hex.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 16:43:46 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/17 15:29:19 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** name and comment to hex
** hex_fill checks if name or comment doesnt
** exceed bytes and fills remaining bytes
*/

static char		*hex_fill(char *str, int size)
{
	int		i;
	char	*name;

	i = 0;
	name = ft_strnew(0);
	if (ft_strlen(str) > (size_t)size)
		ft_error("Name or comment is too large boi");
	while (str[i])
	{
		name = ft_strjoinfree(name, get_hex(str[i], 1));
		i++;
	}
	while (i < size)
	{
		name = ft_strjoinfree(name, ft_strdup("00"));
		i++;
	}
	return (name);
}

void			name_comm_hexify(t_asm **asm_info)
{
	char	*name;
	char	*comment;

	name = hex_fill((*asm_info)->name, PROG_NAME_LENGTH);
	comment = hex_fill((*asm_info)->comment, COMMENT_LENGTH);
	free((*asm_info)->comment);
	free((*asm_info)->name);
	(*asm_info)->name = name;
	(*asm_info)->comment = comment;
}
