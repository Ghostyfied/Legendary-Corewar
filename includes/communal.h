/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   communal.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 12:54:31 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/15 12:54:32 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMUNAL_H
# define COMMUNAL_H

# include "libft.h"
# include "op.h"
# include <stdio.h>
# include <errno.h>

# define MEM(x) 		(x*)ft_memalloc(sizeof(x))

int						get_code_size(int fd);
int						swap_32(int nb);
int						octal_valid(t_byte octal, int nb_arg);

char					*get_comment(int fd);
char					*get_name(int fd);
char					*get_hex(unsigned int nb, int bytesize);

short					swap_16(short nb);

void					check_magic_header(int fd);
void					skip_bytes(int fd, int amount);

#endif
