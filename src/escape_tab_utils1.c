#include "../includes/minishell.h"

int	check_list_file(char **list_file, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (!ft_strncmp(g_main_data.part, list_file[i],
				ft_strlen(g_main_data.part)))
			return (0);
		i++;
	}
	return (1);
}

int	find_index(char **list_file, int len, char *list_elem)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (!ft_strncmp(list_file[i], list_elem, ft_strlen(list_elem) + 1))
			break ;
		i++;
	}
	return (i);
}

int	buf_or_old_buf_hist(char *hist)
{
	int	i;

	i = (int)ft_strlen(hist);
	while (i)
	{
		if (hist[i] == ' ')
		{
			i++;
			break ;
		}
		i--;
	}
	safe_free(g_main_data.part);
	g_main_data.part = ft_substr(hist, i, ft_strlen(hist) - i);
	return (i);
}

int	take_word_part(void)
{
	if (!ft_strlen(g_main_data.buf_hist) || g_main_data.current_tab)
	{
		safe_free(g_main_data.part);
		g_main_data.part = ft_strdup("");
		return (0);
	}
	else if (g_main_data.buf_hist[ft_strlen(g_main_data.buf_hist) - 1] == ' ')
	{
		safe_free(g_main_data.part);
		g_main_data.part = ft_strdup("");
		return (0);
	}
	else if (g_main_data.buf_flag)
	{
		return (buf_or_old_buf_hist(g_main_data.old_buf_hist));
	}
	else
	{
		return (buf_or_old_buf_hist(g_main_data.buf_hist));
	}
}

void	no_buff_case(char **list_files, int len)
{
	char	*tmp;

	safe_free(g_main_data.part);
	g_main_data.part = ft_strdup(list_files[g_main_data.current_tab]);
	tputs(tgetstr("cr", 0), 1, ft_putint);
	tputs(tgetstr("dl", 0), 1, ft_putint);
	print_title();
	tmp = g_main_data.buf_hist;
	g_main_data.buf_hist
		= ft_strjoin(g_main_data.old_buf_hist, g_main_data.part);
	ft_putstr(g_main_data.buf_hist);
	g_main_data.cursor_place = ft_strlen(g_main_data.buf_hist);
	g_main_data.key_amount = g_main_data.cursor_place;
	safe_free(tmp);
	safe_free(g_main_data.part);
	g_main_data.part = NULL;
	g_main_data.current_tab++;
	if (g_main_data.current_tab == len)
		g_main_data.current_tab = 2;
}
