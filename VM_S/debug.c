#include "vm.h"

void	print_champions(t_champ *champs, int champ_nb)
{
	int i;

	i = 0;
	while (i < champ_nb)
	{
		ft_printf("%d\n", champs[i].nb_set);
		ft_printf("%-10s : %s\n", ".name", champs[i].name);
		ft_printf("%-10s : %s\n", ".comment", champs[i].comment);
		ft_printf("%-10s : %d\n", "code_size", champs[i].code_size);
		ft_putendl("");
		i++;
	}
}

void	print_byte(const void *byte, size_t size)
{
	int					idx;
	size_t				i;
	const unsigned char	*b;

	i = 0;
	b = (const unsigned char *)byte;
	while (i < size)
	{
		idx = 7;
		while (idx >= 0)
		{
			if (idx == 3)
				write(1, " ", 1);
			if ((b[i] & (1 << idx)) != 0)
				write(1, "1", 1);
			else
				write(1, "0", 1);
			idx--;
		}
		ft_putendl("");
		i++;
	}
}
