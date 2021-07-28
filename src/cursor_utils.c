#include "../includes/minishell.h"

int	check_ascii(void)
{
	int	i;

	i = 0;
	while (g_main_data.buf_hist[i])
	{
		if (g_main_data.buf_hist[i] >= 0 && g_main_data.buf_hist[i] < 127)
			i++;
		else
			return (0);
	}
	return (1);
}

void	moveback_cursor(void)
{
	int	i;

	if (ft_strlen(g_main_data.buf_hist))
	{
		i = (g_main_data.title_cursor_positions
				+ (int)ft_strlen(g_main_data.buf_hist)) / g_main_data.ws.ws_col;
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
	g_main_data.cursor_place = 0;
}

void	cursor_behaviour(char *tmp2)
{
	int	z;

	if (g_main_data.cursor_place != (int)ft_strlen(g_main_data.buf_hist))
	{
		z = 0;
		while (z < (int)ft_strlen(tmp2))
		{
			tputs(cursor_left, 1, ft_putint);
			z++;
		}
	}
}
