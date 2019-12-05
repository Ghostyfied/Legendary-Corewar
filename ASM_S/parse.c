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

int					check_operation(char *s)
{
	if (ft_strequ(s, "live"))
		return (1);
	else if (ft_strequ(s, "ld"))
		return (2);
	else if (ft_strequ(s, "st"))
		return (3);
	else if (ft_strequ(s, "add"))
		return (4);
	else if (ft_strequ(s, "sub"))
		return (5);
	else if (ft_strequ(s, "and"))
		return (6);
	else if (ft_strequ(s, "or"))
		return (7);
	else if (ft_strequ(s, "xor"))
		return (8);
	else if (ft_strequ(s, "zjmp"))
		return (9);
	else if (ft_strequ(s, "ldi"))
		return (10);
	else if (ft_strequ(s, "sti"))
		return (11);
	else if (ft_strequ(s, "fork"))
		return (12);
	else if (ft_strequ(s, "lld"))
		return (13);
	else if (ft_strequ(s, "lldi"))
		return (14);
	else if (ft_strequ(s, "lfork"))
		return (15);
	else if (ft_strequ(s, "aff"))
		return (16);
	return (0);
}

static t_label		*check_label(char *op)
{
	int		i;
	t_label	*label;

	i = 0;
	if (check_operation(op))
		return (NULL);
	 if (!ft_strchr(op, LABEL_CHAR))
		ft_error("Invalid operation");
	while (op[i] != LABEL_CHAR)
	{
		if (!ft_strchr(LABEL_CHARS, op[i]))
			ft_error("Invalid label");
		i++;
	}
	label = MEM(t_label);
	label->name = ft_strnew(i);
	ft_strncpy(label->name, op, i);
	return (label);
}

static t_label	*get_labels(char **champion, int *i)
{
	t_label		*label;
	char		**split;
	char		**first_op;
	int			idx;

	label = NULL;
	split = ft_strsplit(champion[*i], SEPARATOR_CHAR);
	first_op = ft_strsplit(split[0], ' ');
	label = check_label(first_op[0]);
	return (label);
}

void				parse(char **champion)
{
	int			i;
	t_operation *head;
	/* Check comment and name and IF valid ttranslate */

	head = NULL;
	i = 0;
	// while (champion[i])
	// {
		get_labels(champion, &i);
		i++;
	// }
}