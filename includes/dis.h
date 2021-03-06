/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dis.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 12:54:38 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/17 13:28:59 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIS_H
# define DIS_H

# include "communal.h"

# define CODE_OFFSET	(16 + COMMENT_LENGTH + PROG_NAME_LENGTH)
# define REG			1
# define DIR			2
# define IND			3

typedef	struct			s_arg
{
	int					value;
	int					type;
}						t_arg;

typedef struct			s_operation
{
	int					op_code;
	int					nb_arg;
	t_arg				*args;
	struct s_operation	*next;
}						t_operation;

typedef struct			s_champ
{
	int					code_size;
	char				*name;
	char				*comment;
	t_operation			*operations;
}						t_champ;

void					decode_code(int fd, t_champ *champ);
void					read_file(t_champ *vm, char *file);
void					add_operation(t_operation **head, t_operation *new);
void					free_champ(t_champ *champ);

t_operation				*new_operation(int op_code);

#endif
