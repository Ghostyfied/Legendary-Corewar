/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vm.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 12:55:16 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/15 17:24:01 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "visualizer.h"
# include "communal.h"

# define REG			1
# define DIR			2
# define IND			3
# define ZJUMP			9
# define CODE_OFFSET	(16 + COMMENT_LENGTH + PROG_NAME_LENGTH)
# define GAME			vm->game
# define CURSORS		GAME->cursors
# define CHAMPS			vm->champs
# define ARENA			vm->arena

typedef struct			s_arg
{
	int					size;
	int					value;
	int					type;
}						t_arg;

typedef struct			s_cursor
{
	long				id;
	int					moved;
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
	int					code_size;
	char				*name;
	char				*comment;
	int					lives;
	int					last_live;
	int					starting_pos;
}						t_champ;

typedef struct			s_game
{
	int					winner;
	int					cycles_counter;
	int					live_counter;
	int					cycles_to_die;
	int					check_counter;
	int					checks;
	int					cursors_count;
	long				cursors_id;
	t_cursor			*cursors;
}						t_game;

typedef struct			s_vm
{
	int					arg_idx;
	int					*tab;
	int					champion_count;
	int					champ_nb;
	int					champ_position;
	int					dump;
	int					vflag;
	t_visualizer		*visual;
	t_byte				arena[MEM_SIZE];
	t_champ				*champs;
	t_game				*game;
}						t_vm;

void					check_champion_position(t_champ *champs,
						int champ_count);
void					count_champions(t_vm *vm, char **argv);
void					assign_champ_num(t_vm *vm, int argc, char **argv);
void					ft_arrdel(char **arr);
void					set_no_flag_number(t_vm *vm, int num, int nb);
void					retrieve_flags(t_vm *vm, int argc, char **argv);
void					read_file(t_vm *vm, char *argv, t_champ *champ);
void					setup_game(t_vm *vm);
void					add_cursor(t_cursor **head, t_cursor *new);
void					play_game(t_vm *vm);
void					free_vm(t_vm *vm);
void					dump64(t_vm *vm);
void					game(t_vm *vm);
void					free_cursors(t_cursor *cursor);
void					execute_op(t_vm *vm, t_cursor *c);
void					do_op(t_vm *vm, t_cursor *cursor,
						t_arg *args, int size);
void					put_value(t_byte *arena, int idx, void *value);
void					move_cursor(t_vm *vm, t_cursor *c, int move);
void					retreive_flags_helper(int argc, char **argv,
						int i, t_vm *vm);
void					parse_number(t_vm *vm, char *num);
void					ft_usage(char *name);

int						parse_number_helper(int i, t_vm *vm);
int						ft_arrlen(char **tab);
int						ft_validate_format(char *format, char *str);
int						ft_is_a_number(char *str);
int						get_bytes(t_byte *arena, int idx, int amount);
int						get_arena_index(int current, int move);
int						valid_opcode(t_byte opcode);
int						get_arena_index(int current, int move);

t_cursor				*new_cursor(int	position, int r1, long id);
t_cursor				*copy_cursor(t_cursor *src, int position, long id);
t_cursor				*delete_cursor(t_cursor *head, long cursor_id);

void					live(t_vm *vm, t_cursor *c, t_arg *arg);
void					ld(t_vm *vm, t_cursor *c, t_arg *argument);
void					st(t_vm *vm, t_cursor *c, t_arg *argument);
void					add(t_vm *vm, t_cursor *c, t_arg *argument);
void					sub(t_vm *vm, t_cursor *c, t_arg *argument);

void					and(t_vm *vm, t_cursor *c, t_arg *argument);
void					or(t_vm *vm, t_cursor *c, t_arg *argument);
void					xor(t_vm *vm, t_cursor *c, t_arg *argument);
void					zjmp(t_vm *vm, t_cursor *c, t_arg *argument);
void					ldi(t_vm *vm, t_cursor *c, t_arg *argument);

void					sti(t_vm *vm, t_cursor *c, t_arg *argument);
void					lld(t_vm *vm, t_cursor *c, t_arg *argument);
void					lldi(t_vm *vm, t_cursor *c, t_arg *argument);
void					aff(t_vm *vm, t_cursor *c, t_arg *argument);
void					ft_fork(t_vm *vm, t_cursor *c, t_arg *argument,
						int modulo);

#endif
