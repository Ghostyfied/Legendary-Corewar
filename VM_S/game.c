#include "vm.h"

/*
** EXAMPLES:
** int x = get_2bytes(&ARENA[i]); index vanaf waar je de bytes wilt lezen, geeft een integer terug in kleine endian!
** int y = get_4bytes(&ARENA[i]); index vanaf waar je de bytes wilt lezen, geeft een integer terug in kleine endian!
*/

int			get_2bytes(t_byte *arena)
{
	short b;

	ft_memcpy(&b, arena, 2);
	return (swap_16(b));
}

int			get_4bytes(t_byte *arena)
{
	int b;

	ft_memcpy(&b, arena, 4);
	return (swap_32(b));
}
