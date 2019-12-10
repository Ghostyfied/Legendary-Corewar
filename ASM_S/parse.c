/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 16:24:50 by fhignett       #+#    #+#                */
/*   Updated: 2019/12/10 16:52:40 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		check_comments(char **chmp, int *i)
{
	(*i)++;
	while (chmp[*i][0] == COMMENT_CHAR || !ft_strlen(chmp[*i]))
		(*i)++;
}

/*
** Goes char by char over the string until it finds the LABEL_CHAR.
** If found adds label to t_label linked list.
** Checks if after LABEL_CHAR there is a comment or operation.
** Returns t_label, can also be NULL.
** *i will be incremented correctly so that it continues on the correct line.
*/

static t_label	*get_labels(char **chmp, int *i)
{
	t_label	*label;
	int		j;

	j = 0;
	label = NULL;
	while (chmp[*i][j])
	{
		if (chmp[*i][j] == LABEL_CHAR)
		{
			add_label(&label, new_label(ft_strncpy(ft_strnew(j), chmp[*i], j)));
			if (check_op_on_line(&chmp[*i][j + 1]))
				break ;
			else
			{
				j = 0;
				check_comments(chmp, i);
			}
		}
		else if (!ft_strchr(LABEL_CHARS, chmp[*i][j]))
			break ;
		else
			j++;
	}
	return (label);
}

/*
** Checks all args to get the type.
** Size is the number of arguments teh operation is supposed to have.
*/

static void		get_arg_type(t_operation **op, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if ((*op)->arg[i].op[0] == DIRECT_CHAR)
			(*op)->arg[i].arg = T_DIR;
		else if ((*op)->arg[i].op[0] == 'r')
			(*op)->arg[i].arg = T_REG;
		else
			(*op)->arg[i].arg = T_IND;
		i++;
	}
}

/*
** Get's the correct index to start IF there is a label present.
** Skips the space if present after LABEL_CHAR
** Gets the size of the operation name by
** searching for the first space after LABEL_CHAR.
** Checks if the operation is a valid operation and gets the operation code.
** i is set to the index of first argument.
** String is split from SEPERATOR_CHAR into a char** for each argument.
** Checks if it's got the correct amount of arguments and
** adds it to t_operation struct.
** Then adds operation type to t_arg
*/

static void		get_operation(t_operation **head, char *operation)
{
	int		i;
	int		size;
	char	**args;

	i = chr_idx(operation, LABEL_CHAR);
	i = i && operation[i - 2] == '%' ? 0 : i;
	i = operation[i] == ' ' ? i + 1 : i;
	size = chr_idx(&operation[i], ' ') - 1;
	(*head)->op = check_operation(&operation[i], size);
	if (!(*head)->op)
		ft_error("Invalid operation");
	i += size + 1;
	args = ft_strsplit(&operation[i], SEPARATOR_CHAR);
	i = 0;
	while (i < g_op_tab[(*head)->op].nb_arg)
	{
		if (!args[i])
			ft_error("Missing argument");
		(*head)->arg[i].op = strtrim(args[i]);
		i++;
	}
	if (args[i])
		ft_error("Too many arguments");
	get_arg_type(head, g_op_tab[(*head)->op].nb_arg);
	ft_chararrfree(&args);
}

/*
** Returns the index of where the champion code begins
** after the .name and .comment.
** For each champion line, looks for the label(s) and
** creats a t_operation adding the labels.
** Trims the string, reduces everything to one single space,
** then adds the other information to t_operation. (see t_operation struct)
** Mallocs an int array and adds the size in bytes for each
** command at the size_index for each t_operation.
** Adds the execution code in hex to each t_operation node.
*/

void			parse(char **champion, t_asm **asm_info)
{
	int			i;
	t_operation *head;
	t_operation *op;
	int			*size;

	head = NULL;
	i = get_name_comm(champion, asm_info);
	name_comm_hexify(asm_info);
	while (champion[i])
	{
		op = new_operation(get_labels(champion, &i));
		get_operation(&op, champion[i]);
		add_operation(&head, op);
		i++;
	}
	size = (int*)ft_memalloc(sizeof(int) * (op->size_index + 2));
	calculate_size(head, &size, 0);
	(*asm_info)->exec_code_size = make_exc_code(&head, size);
	(*asm_info)->operations = head;
}
