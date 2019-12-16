

#include "vm.h"

/*
**	
*/
void		set_no_flag_number(t_vm *vm, int num, int nb)
{
	int		i;

	i = 0;
	while (i < vm->count)
	{
		if (vm->champs[i].nb_set == nb)
		{
			set_no_flag_number(vm, num, nb - 1);
			return ;
		}
		i++;
	}
	vm->champs[num].nb_set = nb;
}

/*
**	Check if champs are in right order otherwise swap them around
*/
void		arrange_champs_order(t_vm *vm)
{
	int		n;
	int		i;
	t_champ	champ;

	i = 0;
	while (i < vm->count)
	{
		n = 0;
		while (n < vm->count)
		{
			if (n + 1 < vm->count)
			{
				if (vm->champs[n].nb_set < vm->champs[n + 1].nb_set)
				{
					champ = vm->champs[n];
					vm->champs[n] = vm->champs[n + 1];
					vm->champs[n + 1] = champ;
				}
			}
			n++;
		}
		i++;
	}
}

void			check_champion_position(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->count)
	{
		if (vm->champs[i].nb_set == 0)
			set_no_flag_number(vm, i, -1);
		i++;
	}
	arrange_champs_order(vm);
}

/*
**	Assign correct number to champ coming in the function
*/
void		assign_nbr(t_vm *vm, int num)
{
	int		i;

	i = 0;
	while (i < vm->count)
	{
		if (vm->champs[i].nb_set == num)
			vm->champs[i].nb_set = 0;
		i++;
	}
	vm->champs[vm->index].nb_set = num;
}

/*
**	check whether arg after -n is a number, check whether its within 0-4 (because thats the maximum amount of champs), assign number, read_file if succesful.
*/
void			assign_champ_num(t_vm *vm, int argc, char **argv)
{
	vm->index++;
	if (vm->index < argc)
	{
		if ((ft_is_a_number(argv[vm->index]) == 1))
		{
			if (ft_atoi(argv[vm->index]) > 4 || ft_atoi(argv[vm->index]) < 0)
				ft_error("That position is not available");
			assign_nbr(vm, ft_atoi(argv[vm->index]));
			vm->index++;
		}
		if (vm->index < argc)
			read_file(vm, argv[vm->index], &vm->champs[vm->nb]);
		else
			ft_error("That wont work");
	}
	else
		ft_error("neither will that");
}