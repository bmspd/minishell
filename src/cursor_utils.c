#include "../includes/minishell.h"

int	check_ascii(void)
{
	int	i;

	i = 0;
	while(main_data.buf_hist[i])
	{
		if (main_data.buf_hist[i] >= 0 && main_data.buf_hist[i] < 127)
			i++;
		else
			return (0);
	}
	return (1);
}

void	moveback_cursor(void)
{
	int	i;
	int z;
	if (ft_strlen(main_data.buf_hist))
	{
		i = (main_data.title_cursor_positions
			+ (int)ft_strlen(main_data.buf_hist)) / main_data.ws.ws_col;
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
