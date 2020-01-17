/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   visualizer.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/09 12:15:46 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/17 14:21:34 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include <ncurses.h>
# include "communal.h"

# define INFO_H			66
# define INFO_W			60
# define ARENA_H		66
# define ARENA_W		195
# define PLAYER1_C		COLOR_MAGENTA
# define PLAYER2_C		COLOR_CYAN
# define PLAYER3_C		COLOR_BLUE
# define PLAYER4_C		COLOR_RED
# define VISUAL			vm->visual
# define SLEEP			15000
# define COPIED_CYCLES	50

typedef struct s_vm		t_vm;
typedef struct s_cursor	t_cursor;
typedef struct s_champ	t_champ;

typedef struct			s_visualizer
{
	WINDOW				*arena_win;
	WINDOW				*info_win;
	t_byte				carena[MEM_SIZE];
	t_byte				copied[MEM_SIZE];
}						t_visualizer;

void					visualizer(t_vm *vm, WINDOW *arena_win);
void					info_vis(t_vm *vm, WINDOW *info_win);
void					init_vis(t_vm *vm);
void					end_vis(t_vm *vm);
void					refresh_windows(t_vm *vm, WINDOW *arena_win,
						WINDOW *info_win);
void					get_xy(int index, int *y, int *x);
void					highlight_cursor(t_vm *vm, int prev, int pos);
void					update_arena(t_vm *vm, int pos, int colour);
void					paused(WINDOW *win);
void					reset_champ_lives(t_champ *champs, int champ_count);
void					update_copied(t_vm *vm);

#endif
