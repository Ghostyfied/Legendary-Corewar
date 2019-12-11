#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include <stdio.h>
# include <errno.h>

# define MEM(x) (x*)ft_memalloc(sizeof(x))

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
char					*get_hex(unsigned int nb, int bytesize);

void					name_comm_hexify(t_asm **asm_info);
void					add_label(t_label **head, t_label *new);
void					add_operation(t_operation **head, t_operation *new);
void					parse(char **champion, t_asm **asm_info);
void					calculate_size(t_operation *operations,
						int **size, int i);
void					arg_exc_code(t_operation *tmp,
						t_operation *head, int *size_array);
void					get_arg_type(t_operation **op, int size);

int						make_exc_code(t_operation **op, int *size);
int						get_name_comm(char **champion, t_asm **asm_info);
int						chr_idx(char *s, int c);
int						get_encoding_byte(t_arg *arg);
int						check_operation(char *s, int size);
int						check_op_on_line(char *line);
int						find_label(t_operation *op, char *label,
						int size_idx, int *size);

t_label					*new_label(char *name);

t_operation				*new_operation(t_label *labels);

void					free_asm(t_asm *asm_info);

#endif
