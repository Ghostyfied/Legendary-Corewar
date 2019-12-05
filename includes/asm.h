#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include <errno.h>

# define MEM(x) (x*)ft_memalloc(sizeof(x))

typedef	unsigned char	t_byte;

typedef struct			s_cursor
{
	int					carry;
	int					registry[REG_NUMBER];
}						t_cursor;

typedef	struct			s_arg
{
	int					arg;
	char				*op;
}						t_arg;

typedef	struct			s_label
{
	char				*name;
	int					place;
	struct s_label		*next;
}						t_label;

typedef struct			s_operation
{
	t_label				*label;
	int					op;
	int					arg1;
	int					arg2;
	int					arg3;
	int					size;
	struct s_operation *next;
}						t_operation;


char						**ft_read_file(char *filename);

void						parse(char **champion);

#endif
