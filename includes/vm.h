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
# define GAME			vm->game
# define CURSORS		GAME->cursors
# define CHAMPS			vm->champs
# define ARENA			vm->arena

typedef enum			e_bool
{
	false,
	true
}						t_bool;

typedef struct			s_arg
{
	int					size;
	int					value;
	int					type;
}						t_arg;

typedef struct			s_cursor
{
	long				id;
	int					moved; /* To check if cursor has moved last round, init with true */
	int					carry;
	int					opcode;
	int					last_live;
	int					wait_cycles;
	int					position;
	int					jump;
	int					registry[REG_NUMBER];
	struct s_cursor		*next;
}						t_cursor;

typedef struct			s_champ
{
	int					id;
	int					code_size; /* Size of champions code */
	char				*name;
	char				*comment;
	int					lives;
	int					starting_pos;
}						t_champ;

typedef struct			s_game
{
	int					winner; /* This is the variable showing the winner. It is initialised with the highest player id, and is updated every time operation live is performed. */
	int					cycles_counter;
	int					live_counter;
	int					cycles_to_die;
	int					checks;
	long				cursors_id;
	t_cursor			*cursors;
}						t_game;

typedef struct			s_vm
{
	int					arg_idx; /* Argument index */
	int					*tab; /* Used for Champion positon in array */
	int					champion_count; /* Amount of Champions */
	int					champ_nb; /* Current index of Champs in array */
	int					champ_position; /* Position to multiply for champions in arena */
	int					dump;
	t_byte				arena[MEM_SIZE];
	t_champ				*champs;
	t_game				*game;
}						t_vm;

void					check_champion_position(t_vm *vm);
void					count_champions(t_vm *vm, char **argv);
void					assign_champ_num(t_vm *vm, int argc, char **argv);
void					ft_arrdel(char **arr);
void					set_no_flag_number(t_vm *vm, int num, int nb);
void					retrieve_flags(t_vm *vm, int argc, char **argv);
void					read_file(t_vm *vm, char *argv, t_champ *champ);
void					start_vm(t_vm *vm);
void					setup_game(t_vm *vm);
void					add_cursor(t_cursor **head, t_cursor *new);
void					play_game(t_vm *vm);
void					free_vm(t_vm *vm);
void					dump64(t_vm *vm);
void					dump32(t_vm *vm);
void					game(t_vm *vm);
void					free_cursors(t_cursor *cursor);
void					execute_op(t_cursor *c, t_vm *vm);

int						ft_arrlen(char **tab);
int						ft_validate_format(char *format, char *str);
int						ft_is_a_number(char *str);
int						swap_32(int nb);
int						get_2bytes(t_byte *arena);
int						get_4bytes(t_byte *arena);
int						get_arena_index(int current, int move);
int						octal_valid(t_byte octal, int nb_arg);
int						valid_opcode(t_byte opcode);
int						get_2bytes(t_byte *arena);
int						get_4bytes(t_byte *arena);
int						get_arena_index(int current, int move);

short					swap_16(short nb);

t_cursor				*new_cursor(int	position, int r1, long id);
t_cursor				*copy_cursor(t_cursor *src, int position, long id);
t_cursor				*delete_cursor(t_cursor *head, long cursor_id);

/* DEBUG */
void	print_byte(const void *byte, size_t size);
void	print_champions(t_champ *champs, int champ_nb);
void	print_cursor(t_cursor *cursor, int reg);
void	print_cursors(t_cursor *cursors, int reg);
/* DEBUG */

#endif