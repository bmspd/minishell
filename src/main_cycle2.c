#include "../includes/minishell.h"

void	main_engine(void)
{
	int	fd;

	main_data.counter = 0;
	main_data.flag1 = 0;
	main_data.current_tab = 0;
	safe_free(main_data.part);
	main_data.part = NULL;
	main_data.new_cmd_flag = 1;
	ft_lstadd_back(&main_data.commands, ft_lstnew(NULL));
	init_commands();
	parser(delete_spaces_behind(main_data.buf_hist));
	if (extra_parser() && ft_strncmp(main_data.buf_hist, "\4", 2))
		command_launcher();
	cleaning_foo();
	fd = open_history(O_TRUNC);
	ft_lstadd_front(&main_data.history,
		ft_lstnew_history(main_data.buf_hist,
			(int)ft_strlen(main_data.buf_hist)));
	numerate_history(main_data.history);
	fill_external_history(fd);
}
