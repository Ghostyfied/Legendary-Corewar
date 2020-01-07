/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 16:24:50 by fhignett       #+#    #+#                */
/*   Updated: 2019/12/19 16:53:58 by rvan-ket      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	while (chmp[*i] && chmp[*i][j])
	{
		if (chmp[*i][j] == LABEL_CHAR)
		{
			add_label(&label, new_label(ft_strncpy(ft_strnew(j), chmp[*i], j)));
			if (chmp[*i][j + 1])
				break ;
			j = 0;
			(*i)++;
		}
		else if (!ft_strchr(LABEL_CHARS, chmp[*i][j]))
			break ;
		else
			j++;
	}
	return (label);
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

static int		parse_champion(char **champion, t_operation **head,
				t_operation **op, int *i)
{
	t_label		*labels;

	labels = get_labels(champion, i);
	if (!champion[*i])
	{
		free_labels(labels);
		return (0);
	}
	*op = new_operation(labels);
	get_operation(op, champion[*i]);
	add_operation(head, *op);
	return (1);
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
	int			*size;
	t_operation *op;

	head = NULL;
	i = get_name_comm(champion, asm_info);
	delete_comments(&champion[i], COMMENT_CHAR);
	delete_comments(&champion[i], ALT_COMMENT_CHAR);
	champion = delete_empty_lines(champion, &i);
	name_comm_hexify(asm_info);
	while (champion[i])
	{
		if (!parse_champion(champion, &head, &op, &i))
			break ;
		i++;
	}
	size = (int*)ft_memalloc(sizeof(int) * (op->size_index + 2));
	calculate_size(head, &size, 0);
	(*asm_info)->exec_code_size = make_exc_code(&head, size);
	if ((*asm_info)->exec_code_size > CHAMP_MAX_SIZE)
		ft_error("Code size overload");
	(*asm_info)->operations = head;
	free(size);
	ft_chararrfree(&champion);
}
