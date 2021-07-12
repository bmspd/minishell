#include "../includes/minishell.h"

int escape_ctrl(char *str)
{
	if (str[0] == 12)
	{
		tputs(tgetstr("cl", 0), 1, ft_putint);
		print_title();
		free(main_data.buf_hist);
		main_data.buf_hist = ft_strdup("");
		main_data.cursor_place = 0;
		main_data.history_id = -1;
		return (1);
	}
	return (0);
}
