#include "../includes/minishell.h"

void	main_engine(void)
{
	int	fd;

	g_main_data.counter = 0;
	g_main_data.flag1 = 0;
	g_main_data.current_tab = 0;
	safe_free(g_main_data.part);
	g_main_data.part = NULL;
	g_main_data.new_cmd_flag = 1;
	ft_lstadd_back(&g_main_data.commands, ft_lstnew(NULL));
	init_commands();
	parser(delete_spaces_behind(g_main_data.buf_hist));
	if (extra_parser() && ft_strncmp(g_main_data.buf_hist, "\4", 2))
		command_launcher();
	cleaning_foo();
	fd = open_history(O_TRUNC);
	ft_lstadd_front(&g_main_data.history,
		ft_lstnew_history(g_main_data.buf_hist,
			(int)ft_strlen(g_main_data.buf_hist)));
	numerate_history(g_main_data.history);
	fill_external_history(fd);
}
