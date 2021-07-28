#include "../includes/minishell.h"

int	escape_up(char *str)
{
	if (!ft_strncmp(ESC_UP, str, 4))
	{
		moveback_cursor();
		free(main_data.buf_hist);
		if (main_data.history_id < ft_lstsize(main_data.history))
		{
			main_data.history_id += 1;
			take_history();
		}
		else
		{
			write(1, "\a", 1);
			main_data.buf_hist = ft_strdup("");
			main_data.key_amount = 0;
			main_data.cursor_place = 0;
		}
		return (1);
	}
	return (0);
}

int	escape_down(char *str)
{
	if (!ft_strncmp(ESC_DOWN, str, 4))
	{
		moveback_cursor();
		free(main_data.buf_hist);
		if (main_data.history_id > -1)
		{
			main_data.history_id -= 1;
			take_history();
		}
		else
		{
			write(1, "\a", 1);
			main_data.buf_hist = ft_strdup("");
			main_data.key_amount = 0;
			main_data.cursor_place = 0;
		}
		return (1);
	}
	return (0);
}

int	escape_left(char *str)
{
	if (!ft_strncmp(ESC_LEFT, str, 4))
	{
		if (ft_strlen(main_data.buf_hist)
			+ main_data.title_length <= main_data.ws.ws_col - 1)
		{
			if (main_data.cursor_place == 0
				|| main_data.key_amount < (int)ft_strlen(main_data.buf_hist))
			{
				write(1, "\a", 1);
			}
			else
			{
				if (check_ascii())
				{
					tputs(cursor_left, 1, ft_putint);
					main_data.cursor_place -= 1;
				}
				else
					write(1, "\a", 1);
			}
		}
		return (1);
	}
	return (0);
}

int	escape_right(char *str)
{
	if (!ft_strncmp(ESC_RIGHT, str, 4))
	{
		if (ft_strlen(main_data.buf_hist)
			+ main_data.title_length <= main_data.ws.ws_col - 1)
		{
			if (main_data.cursor_place == (int)ft_strlen(main_data.buf_hist)
				|| main_data.key_amount < (int)ft_strlen(main_data.buf_hist))
				write(1, "\a", 1);
			else if (main_data.cursor_place + main_data.title_length
				== main_data.ws.ws_col - 1)
				write(1, "\a", 1);
			else
			{
				tputs(cursor_right, 1, ft_putint);
				main_data.cursor_place += 1;
			}
		}
		return (1);
	}
	return (0);
}
