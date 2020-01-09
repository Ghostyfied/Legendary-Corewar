/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   visualizer.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/09 12:15:46 by fhignett       #+#    #+#                */
/*   Updated: 2020/01/09 16:14:59 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include <ncurses.h>
# include "communal.h"

# define	INFO_H 66
# define	INFO_W 80
# define	ARENA_H 66 
# define	ARENA_W 195
# define	PLAYER1_C COLOR_MAGENTA
# define	PLAYER2_C COLOR_CYAN
# define	PLAYER3_C COLOR_BLUE
# define	PLAYER4_C COLOR_RED
# define	INFO_C 5

typedef struct s_vm	t_vm;

void				visualizer(t_vm *vm, WINDOW *arena_win);
void				info_vis(t_vm *vm, WINDOW *info_win);
void				init_vis(t_vm *vm);


#endif