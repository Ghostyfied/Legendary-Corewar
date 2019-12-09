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
	ft_printf("ERROR OCCURRED AT : |%s|\n", s);
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

static void			get_arg_type(t_operation **op, int size)
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
		(*head)->arg[i].op = ft_strdup(args[i]);
		i++;
	}
	if (args[i])
		ft_error("Too many arguments");
	get_arg_type(head, op_tab[(*head)->op].nb_arg);
	ft_chararrfree(&args);
}

/* name and comment to hex __ hex_fill checks if name or comment doesnt exeed bytes and fills remaining bytes*/
char				*hex_fill(char *str, int size)
{
	int		i;
	char	*name;

	i = 0;
	name = ft_strnew(0);
	if (ft_strlen(str) > size)
		ft_error("Name or comment is too large boi");
	while(str[i])
	{
		name = ft_strjoinfree(name, get_hex(str[i], 1));
		i++;
	}
	while (i < size)
	{
		name = ft_strjoinfree(name, ft_strdup("00"));
		i++;
	}
	return (name);
}

void				name_comm_hexify(t_asm **asm_info)
{
	char	*name;
	char	*comment;

	name  = hex_fill((*asm_info)->name, CHAMP_MAX_SIZE);
	printf("NAME: %s\n", name);
	comment  = hex_fill((*asm_info)->comment, COMMENT_LENGTH);
	printf("COMMENT: %s\n", comment);
	free((*asm_info)->comment);
	free((*asm_info)->name);
	(*asm_info)->name = name;
	(*asm_info)->comment = comment;
}

void				parse(char **champion, t_asm **asm_info)
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
		get_operation(&op, strtrim(champion[i]));
		add_operation(&head, op);
		i++;
	}
	size = (int*)ft_memalloc(sizeof(int) * (op->size_index + 2));
	calculate_size(head, &size, 0);
	make_exc_code(&head, size);
	ft_putendl("");
}
