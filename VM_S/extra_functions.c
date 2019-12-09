

#include "../includes/vm.h"

/*
**	Check whether the argument after -n is a number
*/
int			ft_is_a_number(char *str)
{
	int		i;

	i = -1;
	if (str[0] == '-' && str[1])
		i++;
	while (i < ft_strlen(str))
	{
		if (ft_isdigit(str[i] == 0))
			return (0);
	}
	return (1);
}