#include "../includes/minishell.h"

static void	deletion(void)
{
	char	*tmp;
	char	*tmp2;

	tputs(cursor_left, 1, ft_putint);
	g_main_data.cursor_place -= 1;
	tputs(tgetstr("dc", 0), 1, ft_putint);
	tmp = ft_substr(g_main_data.buf_hist, 0, g_main_data.cursor_place);
	tmp2 = ft_substr(g_main_data.buf_hist, g_main_data.cursor_place + 1,
			 ft_strlen(g_main_data.buf_hist) - g_main_data.cursor_place);
	free(g_main_data.buf_hist);
	g_main_data.buf_hist = ft_strjoin(tmp, tmp2);
	safe_free(g_main_data.old_buf_hist);
	g_main_data.old_buf_hist = ft_strdup(g_main_data.buf_hist);
	free(tmp);
	free(tmp2);
}

int	escape_backspace(char *str)
{
	if (!strcmp(str, ESC_BACKSPACE))
	{
		if (!ft_strlen(g_main_data.buf_hist)
			|| g_main_data.cursor_place == 0
			|| g_main_data.key_amount < (int)ft_strlen(g_main_data.buf_hist))
			write(1, "\a", 1);
		else
		{
			if (check_ascii())
				deletion();
			else
				write(1, "\a", 1);
		}
		safe_free(g_main_data.part);
		g_main_data.part = NULL;
		g_main_data.current_tab = 0;
		return (1);
	}
	return (0);
}
