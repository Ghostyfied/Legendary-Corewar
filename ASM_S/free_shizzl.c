#include "asm.h"

void		free_labels(t_label	*label)
{
	t_label	*temp;

	while (label)
	{
		temp = label;
		label = label->next;
		free(temp->name);
		free(temp);
	}
}
void		free_asm(t_asm *asm_info)
{
	t_operation *temp;

	free(asm_info->name);
	free(asm_info->comment);
	while (asm_info->operations)
	{
		temp = asm_info->operations;
		asm_info->operations = asm_info->operations->next;
		free(temp->executable);
		free_labels(temp->labels);
		free(temp->arg[0].op);
		free(temp->arg[1].op);
		free(temp->arg[2].op);
		free(temp);
	}
}