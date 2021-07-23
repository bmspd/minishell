#include "../includes/minishell.h"

void	safe_free(char *element)
{
	if (element)
		free(element);
}

void	cleaning_foo(void)
{
	t_list	*tmp;
	int		k;

	while (main_data.commands)
	{
		tmp = NULL;
		k = 0;
		while (main_data.commands->commands[k])
			free(main_data.commands->commands[k++]);
		free(main_data.commands->commands[k]);
		free(main_data.commands->commands);
		free(main_data.commands->flag);
		if (main_data.commands->next)
			tmp = main_data.commands->next;
		free(main_data.commands);
		main_data.commands = tmp;
	}
	main_data.commands = NULL;
	main_data.null_flag = 0;
	main_data.key_amount = 0;
	main_data.history_id = -1;
	main_data.cursor_place = 0;
}
