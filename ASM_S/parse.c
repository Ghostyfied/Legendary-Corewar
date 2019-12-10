#include "asm.h"

/*
** Returns the index + 1 of the char given in the parameters.
** If not found index 0 is returned.
*/

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

/*
** Checks to see if operation is valid.
** Compares (size)char of the string with all operations listed in op.c.
** Returns operation code
*/

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

/*
** Checks the characters afte the LABEL_CHAR
*/

static int			check_op_on_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == COMMENT_CHAR)
			return (0);
		else if (line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

/*
** Goes char by char over the string until it finds the LABEL_CHAR.
** If found adds label to t_label linked list.
** Checks if after LABEL_CHAR there is a comment or operation.
** Returns t_label, can also be NULL.
** *i will be incremented correctly so that it continues on the correct line.
*/

static t_label		*get_labels(char **champion, int *i)
{
	t_label	*label;
	int		j;

	j = 0;
	label = NULL;
	while (champion[*i][j])
	{
		if (champion[*i][j] == LABEL_CHAR)
		{
			add_label(&label, new_label(ft_strncpy(ft_strnew(j), champion[*i], j)));
			if (check_op_on_line(&champion[*i][j + 1]))
				break ;
			else
			{
				j = 0;
				(*i)++;
				while (champion[*i][j] == COMMENT_CHAR || !ft_strlen(champion[*i]))
					(*i)++;
			}
		}
		else if (!ft_strchr(LABEL_CHARS, champion[*i][j]))
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

/*
** Get's the correct index to start IF there is a label present.
** Skips the space if present after LABEL_CHAR
** Gets the size of the operation name by searching for the first space after LABEL_CHAR.
** Checks if the operation is a valid operation and gets the operation code.
** i is set to the index of first argument.
** String is split from SEPERATOR_CHAR into a char** for each argument.
** Checks if it's got the correct amount of arguments and adds it to t_operation struct.
** Then adds operation type to t_arg
*/

static void			get_operation(t_operation **head, char *operation)
{
	int		i;
	int		size;
	char	**args;

	i = chr_idx(operation, LABEL_CHAR);
	if (i && operation[i - 2] == '%')
		i = 0;
	if (operation[i] == ' ')
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
		(*head)->arg[i].op = strtrim(args[i]);
		i++;
	}
	if (args[i])
		ft_error("Too many arguments");
	get_arg_type(head, op_tab[(*head)->op].nb_arg);
	ft_chararrfree(&args);
}

/*
** name and comment to hex
** hex_fill checks if name or comment doesnt exceed bytes and fills remaining bytes
*/

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

	name  = hex_fill((*asm_info)->name, PROG_NAME_LENGTH);
	comment  = hex_fill((*asm_info)->comment, COMMENT_LENGTH);
	free((*asm_info)->comment);
	free((*asm_info)->name);
	(*asm_info)->name = name;
	(*asm_info)->comment = comment;
}

/*
** Returns the index of where the champion code begins after the .name and .comment.
** For each champion line, looks for the label(s) and creats a t_operation adding the labels.
** Trims the string, reduces everything to one single space,
** then adds the other information to t_operation. (see t_operation struct)
** Mallocs an int array and adds the size in bytes for each command at the size_index for each t_operation.
** Adds the execution code in hex to each t_operation node.
*/

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
		get_operation(&op, champion[i]);
		add_operation(&head, op);
		i++;
	}
	size = (int*)ft_memalloc(sizeof(int) * (op->size_index + 2));
	calculate_size(head, &size, 0);
	(*asm_info)->exec_code_size = make_exc_code(&head, size);
	(*asm_info)->operations = head;
}
