

#include "vm.h"

/*
**	Keep adding size of last code up to bit_swap and check the code in the file in the other functions.
*/
// void		validate_champion(t_champ *champ, char *content)
// {
// 	size_t		i;
// 	size_t		bit_swap;

// 	bit_swap = 0;
// 	check_magic_header(champ, content);
// 	i = (size_t)check_prog_name(champ, content, bit_swap);
// 	bit_swap = i + bit_swap + sizeof(champ->prog_size);
// 	i = check_prog_size(champ, content, bit_swap);
// 	bit_swap = i + bit_swap;
// 	i = check_comment(champ, content, bit_swap);
// 	bit_swap = i + bit_swap + 4;
// 	check_program(champ, content, bit_swap);
// }

/*
**	Read file, put everything in content. set number of champs higher, set filename, set prog_size, send to champion checker.
*/
void		read_file(t_vm *vm, char *argv, int num)
{
	t_byte	*content;
	int		fd;
	int		size;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_error(strerror(errno));
	size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if (size < 0)
		ft_error("That is not a valid file");
	content = ft_strnew((size_t)size);
	read(fd, content, (size_t)size);
	vm->champs[num].nb = num + 1;
	vm->champs[num].filename = argv;
	vm->champs[num].real_prog_size = (size_t)size;
	// validate_champion(&vm->champs[num], content);
	free(content);
	vm->nb++;
}