#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"

typedef	unsigned char	t_byte;

typedef struct			s_cursor
{
	int					carry;
}						t_cursor;

int						ft_read_file(char *filename);

#endif
