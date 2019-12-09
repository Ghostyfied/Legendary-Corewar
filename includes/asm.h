#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
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
	struct s_operation *next;
}						t_operation;

typedef	struct			s_asm
{
	t_operation			*operations;
	char				*name;
	char				*comment;
	// struct s_label		*next;
}						t_asm;

char					**ft_read_file(char *filename);

void					add_label(t_label **head, t_label *new);
void					add_operation(t_operation **head, t_operation *new);
void					parse(char **champion);
void					calculate_size(t_operation *operations, int **size, int i);
void					make_exc_code(t_operation **op, int *size);

int						get_name_comm(char **champion);

t_label					*new_label(char *name);

t_operation				*new_operation(t_label *labels);

/* DEBUG */
void			print_labels(t_label *lbl);
void			print_op(t_operation *op);
/* DEBUG */

#endif
