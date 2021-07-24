#include "../includes/minishell.h"

int	escape_ctrl(char *str)
{
	if (str[0] == 12)
	{
		tputs(tgetstr("cl", 0), 1, ft_putint);
		print_title();
		free(main_data.buf_hist);
		main_data.buf_hist = ft_strdup("");
		main_data.cursor_place = 0;
		main_data.history_id = -1;
		main_data.key_amount = 0;
		return (1);
	}
	return (0);
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
		len = (int)count_arr(list_files);
		if (len == 2)
		{
			write(1, "\a", 1);
			free_arr(list_files, len);
			return (1);
		}
		i = take_word_part();
		if_zero_current_tab();
		if (main_data.part && !ft_strncmp(main_data.part, "", 1))
			no_buff_case(list_files, len);
		else
			is_buff_case(list_files, len, &list_elem, i);
		free_arr(list_files, len);
		return (1);
	}
	return (0);
}
