#include "vm.h"

void	print_champions(t_champ *champs, int champ_nb)
{
	int i;

	i = 0;
	while (i < champ_nb)
	{
		ft_printf("%d\n", champs[i].id);
		ft_printf("%-10s : %s\n", ".name", champs[i].name);
		ft_printf("%-10s : %s\n", ".comment", champs[i].comment);
		ft_printf("%-10s : %d\n", "code_size", champs[i].code_size);
		ft_printf("%-10s : %d\n", "start_pos", champs[i].starting_pos);
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

void	print_cursor(t_cursor *cursor)
{
	int i = 0;

	ft_printf("%-8s : %d\n", "id", cursor->id);
	ft_printf("%-8s : %d\n", "position", cursor->position);
	while (i < REG_NUMBER)
	{
		ft_printf(" r%-2d : %d\n", i, cursor->registry[i]);
		i++;
	}
	ft_putendl("");
}

void	print_cursors(t_cursor *cursors)
{
	if (!cursors)
		return ;
	print_cursor(cursors);
	print_cursors(cursors->next);
}
