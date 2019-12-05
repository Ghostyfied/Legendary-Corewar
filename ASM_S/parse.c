#include "asm.h"

static int			chr_idx(char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

static int			check_operation(char *s, int size)
{
	int i;

	i = 1;
	while (i <= 16)
	{
		if (ft_strncmp(s, op_tab[i].name, size) == 0)
			return (op_tab[i].opcode);
		i++;
	}
	return (0);
}

static t_label		*get_labels(char **champion, int *i)
{
	t_label	*label;
	int		j;

	j = 0;
	label = NULL;
	while (champion[*i][j])
	{
		if (champion[*i][j] == LABEL_CHAR)
			add_label(&label, new_label(ft_strncpy(ft_strnew(j), champion[*i], j)));
		else if (!ft_strchr(LABEL_CHARS, champion[*i][j]))
			break ;
		j++;
		if (!champion[*i][j])
		{
			j = 0;
			(*i)++;
		}
	}
	return (label);
}

static void			get_operation(t_operation **head, char *operation)
{
	int		i;
	int		size;
	char	**args;

	i = chr_idx(operation, LABEL_CHAR);
	if (i && operation[i - 2] == '%')
		i = 0;
	while (operation[i] == ' ' || operation[i] == '\t')
		i++;
	size = chr_idx(&operation[i], ' ') - 1;
	(*head)->op = check_operation(&operation[i], size);
	if (!(*head)->op)
		ft_error("Invalid operation");
	i += size + 1;
	args = ft_strsplit(&operation[i], SEPARATOR_CHAR);
	i = 0;
	while (i < op_tab[(*head)->op].nb_arg)
	{
		if (!args[i])
			ft_error("Missing argument");
		(*head)->arg[i].op = ft_strtrim(args[i]);
		i++;
	}
	if (args[i])
		ft_error("Too many arguments");
	ft_chararrfree(&args);
}

void				parse(char **champion)
{
	int			i;
	t_operation *head;
	/* Check comment and name and IF valid ttranslate */

	head = NULL;
	i = get_name_comm(champion);

	while (champion[i])
	{
		add_operation(&head, new_operation(get_labels(champion, &i)));
		get_operation(&head, champion[i]);
		i++;
	}
	calculate_size(&head);
}
