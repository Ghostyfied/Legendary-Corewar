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

int					check_operation(char *s, int size)
{
	if (ft_strncmp(s, "live", size) == 0)
		return (1);
	else if (ft_strncmp(s, "ld", size) == 0)
		return (2);
	else if (ft_strncmp(s, "st", size) == 0)
		return (3);
	else if (ft_strncmp(s, "add", size) == 0)
		return (4);
	else if (ft_strncmp(s, "sub", size) == 0)
		return (5);
	else if (ft_strncmp(s, "and", size) == 0)
		return (6);
	else if (ft_strncmp(s, "or", size) == 0)
		return (7);
	else if (ft_strncmp(s, "xor", size) == 0)
		return (8);
	else if (ft_strncmp(s, "zjmp", size) == 0)
		return (9);
	else if (ft_strncmp(s, "ldi", size) == 0)
		return (10);
	else if (ft_strncmp(s, "sti", size) == 0)
		return (11);
	else if (ft_strncmp(s, "fork", size) == 0)
		return (12);
	else if (ft_strncmp(s, "lld", size) == 0)
		return (13);
	else if (ft_strncmp(s, "lldi", size) == 0)
		return (14);
	else if (ft_strncmp(s, "lfork", size) == 0)
		return (15);
	else if (ft_strncmp(s, "aff", size) == 0)
		return (16);
	return (0);
}

static t_label		*new_label(char *name)
{
	t_label *label;

	label = MEM(t_label);
	label->name = name;
	return (label);
}

static void			add_label(t_label **head, t_label *new)
{
	if (!head)
		return ;
	new->next = *head;
	*head = new;
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

static void			add_operation(t_operation **head, t_operation *new)
{
	if (!head)
		return ;
	new->next = *head;
	*head = new;
}

static t_operation	*new_operation(t_label *labels)
{
	t_operation *op;

	op = MEM(t_operation);
	op->labels = labels;
	return (op);
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
	if (args[0])
	{
		(*head)->arg1.op = ft_strtrim(args[0]);
		if (args[1])
		{
			(*head)->arg2.op = ft_strtrim(args[1]);
			if (args[2])
				(*head)->arg3.op = ft_strtrim(args[2]);
		}
	}
	ft_chararrfree(&args);
}

void				print_labels(t_label *lbl)
{
	if (!lbl)
		return ;
	print_labels(lbl->next);
	ft_putstr("\t");
	ft_putendl(lbl->name);
}

static void			print_operations(t_operation *op)
{
	if (!op)
		return ;
	print_operations(op->next);
	ft_putendl("---------");
	ft_putendl("labels:");
	print_labels(op->labels);
	ft_printf("operation: %d\n", op->op);
	if (op->arg1.op)
	{
		ft_putstr("arg1 : ");
		ft_putendl(op->arg1.op);
	}
	if (op->arg2.op)
	{
		ft_putstr("arg2 : ");
		ft_putendl(op->arg2.op);
	}
	if (op->arg3.op)
	{
		ft_putstr("arg3 : ");
		ft_putendl(op->arg3.op);
	}
	ft_putendl("---------");
}

void				parse(char **champion)
{
	int			i;
	t_operation *head;
	/* Check comment and name and IF valid ttranslate */

	head = NULL;
	i = 0;
	while (champion[i])
	{
		// ft_putendl(champion[i]);
		add_operation(&head, new_operation(get_labels(champion, &i)));
		get_operation(&head, champion[i]);
		i++;
	}
	print_operations(head);
}