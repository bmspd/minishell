#include "../includes/minishell.h"

int	escape_ctrl(char *str)
{
	if (str[0] == 12)
	{
		tputs(tgetstr("cl", 0), 1, ft_putint);
		print_title();
		free(g_main_data.buf_hist);
		g_main_data.buf_hist = ft_strdup("");
		g_main_data.cursor_place = 0;
		g_main_data.history_id = -1;
		g_main_data.key_amount = 0;
		return (1);
	}
	return (0);
}

static int	empty_folder(int len, char **list_files)
{
	if (len == 2)
	{
		write(1, "\a", 1);
		free_arr(list_files, len);
		return (1);
	}
	return (0);
}

static char	*if_folder_changed(char *list_elem)
{
	static char	*pwd;
	char		*pwd_new;

	pwd_new = get_pwd();
	if ((ft_strncmp(pwd_new, pwd, ft_strlen(pwd_new))
			|| ft_strncmp(pwd, pwd_new, ft_strlen(pwd)))
		|| g_main_data.new_cmd_flag)
	{
		safe_free(pwd);
		pwd = get_pwd();
		safe_free(list_elem);
		list_elem = NULL;
		g_main_data.new_cmd_flag = 0;
	}
	free(pwd_new);
	return (list_elem);
}

int	escape_tab(char *str)
{
	char		**list_files;
	int			i;
	static char	*list_elem;
	int			len;

	if (!ft_strncmp(str, "\t", 2))
	{
		list_files = create_list_file();
		list_elem = if_folder_changed(list_elem);
		len = (int)count_arr(list_files);
		if (empty_folder(len, list_files))
			return (1);
		i = take_word_part();
		if_zero_current_tab();
		if (g_main_data.part && !ft_strncmp(g_main_data.part, "", 1))
			no_buff_case(list_files, len);
		else
			is_buff_case(list_files, len, &list_elem, i);
		free_arr(list_files, len);
		return (1);
	}
	return (0);
}
