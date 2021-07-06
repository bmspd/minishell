#include "../includes/minishell.h"

void	moveback_cursor(void)
{
	int i;

	if (ft_strlen(main_data.buf_hist))
	{
		i = (main_data.title_length + (int)ft_strlen(main_data.buf_hist)) / main_data.ws.ws_col;
		while (i)
		{
			tputs(tgetstr("cr", 0), 1, ft_putint);
			tputs(tgetstr("dl", 0), 1, ft_putint);
			tputs(tgetstr("up", 0), 1, ft_putint);
			i--;
		}

	}
	tputs(tgetstr("cr", 0), 1, ft_putint);
	tputs(tgetstr("dl", 0), 1, ft_putint);
	print_title();
	main_data.cursor_place = 0;
}