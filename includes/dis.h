#ifndef DIS_H
# define DIS_H

# include "libft.h"
# include "op.h"
# include <stdio.h>
# include <errno.h>

# define MEM(x)			(x*)ft_memalloc(sizeof(x))
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
void					check_magic_header(int fd);
void					skip_bytes(int fd, int amount);

char					*get_comment(int fd);
char					*get_name(int fd);

short					swap_16(short nb);

int						swap_32(int nb);
int						octal_valid(t_byte octal, int nb_arg);
int						get_code_size(int fd);

t_operation 			*new_operation(int op_code);

#endif
