/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 16:50:34 by fhignett       #+#    #+#                */
/*   Updated: 2019/12/12 11:01:42 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Using bitwise operators gets the correct encoding byte.
** T_REG = 01 (1)
** T_DIR = 10 (2)
** T_IND = 11 (3)
*/

int	get_encoding_byte(t_arg *arg)
{
	t_byte	byte;
	int		arg1;
	int		arg2;
	int		arg3;


	byte = 0;
	arg1 = arg[0].arg == T_IND ? 3 : arg[0].arg;
	arg2 = arg[1].arg == T_IND ? 3 : arg[1].arg;
	arg3 = arg[2].arg == T_IND ? 3 : arg[2].arg;
	byte = byte | arg1;
	byte = (byte << 2) | arg2;
	byte = (byte << 2) | arg3;
	return (byte << 2);
}

/*
** Returns the index + 1 of the char given in the parameters.
** If not found index 0 is returned.
*/

int	chr_idx(char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

/*
** Checks to see if operation is valid.
** Compares (size)char of the string with all operations listed in op.c.
** Returns operation code
*/

int	check_operation(char *s, int size)
{
	int i;

	i = 1;
	while (i <= 16)
	{
		if (ft_strncmp(s, g_op_tab[i].name, size) == 0)
			return (g_op_tab[i].opcode);
		i++;
	}
	ft_printf("ERROR OCCURRED AT : -> %s <-\n", s);
	return (0);
}
