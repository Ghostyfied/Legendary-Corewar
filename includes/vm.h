#ifndef VM_H
# define VM_H
# include "op.h"

typedef struct			s_player
{
	char				*name;
	int					num;
	struct s_player		*next;
}						t_player;

typedef struct			s_vm
{
	char				*arena[MEM_SIZE];
	t_player			*players[MAX_PLAYERS];
	int					player_number;
}						t_vm;

int			validate_champions(int argc, char **argv, t_vm *vm);

#endif