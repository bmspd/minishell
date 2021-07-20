#include "../includes/minishell.h"

static void	deletion(void)
{
	char	*tmp;
	char	*tmp2;

	tputs(cursor_left, 1, ft_putint);
	main_data.cursor_place -= 1;
	tputs(tgetstr("dc", 0), 1, ft_putint);
	tmp = ft_substr(main_data.buf_hist, 0, main_data.cursor_place);
	tmp2 = ft_substr(main_data.buf_hist, main_data.cursor_place + 1,
			 ft_strlen(main_data.buf_hist) - main_data.cursor_place);
	free(main_data.buf_hist);
	main_data.buf_hist = ft_strjoin(tmp, tmp2);
	safe_free(main_data.old_buf_hist);
	main_data.old_buf_hist = ft_strdup(main_data.buf_hist);
	free(tmp);
	free(tmp2);
}

int	escape_backspace(char *str)
{
	if (!strcmp(str, ESC_BACKSPACE))
	{
		if (!ft_strlen(main_data.buf_hist)
			|| main_data.cursor_place == 0
			|| main_data.key_amount < ft_strlen(main_data.buf_hist))
			write(1, "\a", 1);
		else
			deletion();
		safe_free(main_data.part);
		main_data.part = NULL;
		main_data.current_tab = 0;
		return (1);
	}
	return (0);
}
