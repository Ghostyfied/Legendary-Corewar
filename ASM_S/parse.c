#include "asm.h"



static t_operation	*create_operation(char **op)
{

}

void				parse(char **champion)
{
	int			i;
	t_operation *head;
	/* Check comment and name and IF valid ttranslate */

	head = NULL;
	while (champion[i])
	{
		create_operation(ft_strsplit(champion[i], SEPARATOR_CHAR));
		i++;
	}
}