#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"

typedef	unsigned char	t_byte;

typedef struct			s_cursor
{
	int					carry;
}						t_cursor;

int						ft_compile(char *filename, char *new_filename);

#endif
