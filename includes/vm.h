#ifndef VM_H
# define VM_H

# include "op.h"
# include "libft.h"

typedef struct			s_cursor
{
	int					carry;
	int					registry[REG_NUMBER];
}						t_cursor;

typedef struct			s_champ
{
	int					nb;
	int					nb_set;
	int					start_pos;
	char				*filename;
	int					last_live;
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	size_t				real_prog_size;
	char				comment[COMMENT_LENGTH + 1];
	char				*program;
	int					carr_count;
}						t_champ;


typedef struct			s_vm
{
	int					index;
	int					count;
	int					dump;
	int					speed;
	int					max_checks;
	int					nb;
	int					car_count;
	int					winner;
	t_champ				*champs;
}						t_vm;

void			check_champion_position(t_vm *vm);
void			count_champions(t_vm *vm, char **argv);
void			assign_champ_num(t_vm *vm, int argc, char **argv);

// static int		ft_is_a_number(char *str);

int				ft_arrlen(char **tab);
void			ft_arrdel(char **arr);
void			set_no_flag_number(t_vm *vm, int num, int nb);
int				ft_is_a_number(char *str);
void			retrieve_flags(t_vm *vm, int argc, char **argv);
void			read_file(t_vm *vm, char *argv, int num);


#endif