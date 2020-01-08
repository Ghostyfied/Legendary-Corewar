#ifndef COMMUNAL_H
# define COMMUNAL_H

# include "libft.h"
# include "op.h"
# include <stdio.h>
# include <errno.h>

# define MEM(x) 		(x*)ft_memalloc(sizeof(x))

typedef enum			e_bool
{
	false,
	true
}						t_bool;

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