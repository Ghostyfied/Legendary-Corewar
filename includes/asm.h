/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 12:54:13 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/15 16:37:36 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "communal.h"

typedef	struct			s_arg
{
	int					arg;
	char				*op;
}						t_arg;

typedef	struct			s_label
{
	char				*name;
	struct s_label		*next;
}						t_label;

typedef struct			s_operation
{
	int					size_index;
	t_label				*labels;
	int					op;
	t_arg				arg[3];
	char				*executable;
	struct s_operation	*next;
}						t_operation;

typedef	struct			s_asm
{
	t_operation			*operations;
	int					exec_code_size;
	char				*name;
	char				*comment;
}						t_asm;

char					**ft_read_file(char *filename);
char					*strtrim(char *s);
char					**delete_empty_lines(char **old, int *idx);

void					name_comm_hexify(t_asm **asm_info);
void					add_label(t_label **head, t_label *new);
void					add_operation(t_operation **head, t_operation *new);
void					parse(char **champion, t_asm **asm_info);
void					calculate_size(t_operation *operations,
						int **size, int i);
void					arg_exc_code(t_operation *tmp,
						t_operation *head, int *size_array);
void					get_arg_type(t_operation **op, int size);
void					delete_comments(char **champion, char comment_char);
void					free_labels(t_label *label);
void					ft_usage(char *name);

int						make_exc_code(t_operation **op, int *size);
int						get_name_comm(char **champion, t_asm **asm_info);
int						chr_idx(char *s, int c);
int						get_encoding_byte(t_arg *args);
int						check_operation(char *s, int size);
int						find_label(t_operation *op, char *label,
						int size_idx, int *size);

t_label					*new_label(char *name);

t_operation				*new_operation(t_label *labels);

void					free_asm(t_asm *asm_info);

#endif
