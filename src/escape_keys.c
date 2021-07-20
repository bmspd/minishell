#include "../includes/minishell.h"

int escape_up(char *str)
{
	if (!strcmp(str, ESC_UP))
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

int escape_down(char *str)
{
	if (!strcmp(str, ESC_DOWN))
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

int escape_left(char *str)
{
	if (!strcmp(str, ESC_LEFT))
	{
		if (ft_strlen(main_data.buf_hist) + main_data.title_length <= main_data.ws.ws_col - 1)
		{
			if (main_data.cursor_place == 0 || main_data.key_amount < ft_strlen(main_data.buf_hist))
			{
				write(1, "\a", 1);
				//printf("[%d]\n", main_data.key_amount);
			}
			else
			{
				//printf("[%d]\n", main_data.key_amount);
				tputs(cursor_left, 1, ft_putint);
				main_data.cursor_place -= 1;
			}
		}
		return (1);
	}
	return (0);
}

int	escape_right(char *str)
{
	if (!strcmp(str, ESC_RIGHT))
	{
		if (ft_strlen(main_data.buf_hist) + main_data.title_length <= main_data.ws.ws_col - 1)
		{
			if (main_data.cursor_place == ft_strlen(main_data.buf_hist)  || main_data.key_amount < ft_strlen(main_data.buf_hist))
				write(1, "\a", 1);
			else if (main_data.cursor_place + main_data.title_length == main_data.ws.ws_col - 1)
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

int	escape_backspace(char *str)
{
	if (!strcmp(str, ESC_BACKSPACE)) {
		if (!ft_strlen(main_data.buf_hist) || main_data.cursor_place == 0  || main_data.key_amount < ft_strlen(main_data.buf_hist))
		{
			write(1, "\a", 1);
			//printf("[%d] : [%d]\n", main_data.key_amount, ft_strlen(main_data.buf_hist));
		}
		else
		{
			tputs(cursor_left, 1, ft_putint);
			main_data.cursor_place -= 1;
			tputs(tgetstr("dc", 0), 1, ft_putint);
			char *tmp = ft_substr(main_data.buf_hist, 0, main_data.cursor_place);
			char *tmp2 = ft_substr(main_data.buf_hist, main_data.cursor_place + 1,
								   ft_strlen(main_data.buf_hist) - main_data.cursor_place);
			free(main_data.buf_hist);
			main_data.buf_hist = ft_strjoin(tmp, tmp2);
            safe_free(main_data.old_buf_hist); //added!
			main_data.old_buf_hist = ft_strdup(main_data.buf_hist); //added!
			free(tmp);
			free(tmp2);

		}
		//printf("WTF\n");
        safe_free(main_data.part);
		main_data.part = NULL;
		main_data.current_tab = 0;
		return (1);
	}
	return (0);
}
