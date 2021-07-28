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

	while (g_main_data.commands)
	{
		tmp = NULL;
		k = 0;
		while (g_main_data.commands->commands[k])
			free(g_main_data.commands->commands[k++]);
		free(g_main_data.commands->commands[k]);
		free(g_main_data.commands->commands);
		free(g_main_data.commands->flag);
		if (g_main_data.commands->next)
			tmp = g_main_data.commands->next;
		free(g_main_data.commands);
		g_main_data.commands = tmp;
	}
	g_main_data.commands = NULL;
	g_main_data.null_flag = 0;
	g_main_data.key_amount = 0;
	g_main_data.history_id = -1;
	g_main_data.cursor_place = 0;
}
