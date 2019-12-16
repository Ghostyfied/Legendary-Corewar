#ifndef VM_H
# define VM_H

# include "op.h"
# include "libft.h"
# include <errno.h>

# define MEM(x)			(x*)ft_memalloc(sizeof(x))
# define REG			1
# define DIR			2
# define IND			3
# define CODE_OFFSET	(16 + COMMENT_LENGTH + PROG_NAME_LENGTH)

typedef struct			s_cursor
{
	int					id;
	int					carry;
	int					registry[REG_NUMBER];
	int					opcode;
	int					jump;
	int					last_live;
	int					wait_cycles;
	int					position;
	struct s_cursor		*next;
}						t_cursor;

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
	int					nb_set;
	int					code_size;
	char				*name;
	char				*comment;
	t_operation			*operations;
}						t_champ;

typedef struct			s_vm
{
	int					arg_idx;
	int					champion_count;
	int					dump;
	int					speed;
	int					max_checks;
	int					champ_nb;
	int					car_count;
	int					winner;
	int					champ_position;
	t_byte				arena[MEM_SIZE];
	t_champ				*champs;
}						t_vm;

void					check_champion_position(t_vm *vm);
void					count_champions(t_vm *vm, char **argv);
void					assign_champ_num(t_vm *vm, int argc, char **argv);
void					ft_arrdel(char **arr);
void					set_no_flag_number(t_vm *vm, int num, int nb);
void					retrieve_flags(t_vm *vm, int argc, char **argv);
void					read_file(t_vm *vm, char *argv, t_champ *champ);
void					decode_code(int fd, t_champ *champ);
void					add_operation(t_operation **head, t_operation *new);
void					start_vm(t_vm *vm);

t_operation				*new_operation(int op_code);

int						ft_arrlen(char **tab);
int						ft_is_a_number(char *str);
int						swap_32(int nb);

short					swap_16(short nb);

/* DEBUG */
void	print_byte(const void *byte, size_t size);
void	print_champions(t_champ *champs, int champ_nb);
/* DEBUG */

#endif