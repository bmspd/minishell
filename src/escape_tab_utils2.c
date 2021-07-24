#include "../includes/minishell.h"

int	fill_index_take_length(int *index, char **list_files,
							  int len, char *list_elem)
{
	int	length;

	if (!list_elem)
	{
		length = 10;
		*index = 0;
	}
	else
	{
		length = (int)ft_strlen(list_elem) + 1;
		*index = find_index(list_files, len, list_elem);
	}
	return (length);
}

char	*choose_list_elem(char **list_files, int len, char *list_elem, int z)
{
	int	index;
	int	length;

	length = fill_index_take_length(&index, list_files, len, list_elem);
	while (z < len)
	{
		if (!list_elem && !ft_strncmp(main_data.part,
				list_files[index], ft_strlen(main_data.part)))
		{
			safe_free(list_elem);
			list_elem = ft_strdup(list_files[index]);
		}
		else if (!list_elem && !ft_strncmp(main_data.part,
				 list_files[index], ft_strlen(main_data.part))
			 && ft_strncmp(list_files[index], list_elem, length))
		{
			safe_free(list_elem);
			list_elem = ft_strdup(list_files[index]);
		}
		index++;
		if (index == len)
			index = 0;
		z++;
	}
	return (list_elem);
}

void	autocomplete(char *list_elem, int i)
{
	char	*tmp;

	tputs(tgetstr("cr", 0), 1, ft_putint);
	tputs(tgetstr("dl", 0), 1, ft_putint);
	print_title();
	tmp = ft_substr(main_data.buf_hist, 0, i);
	safe_free(main_data.buf_hist);
	main_data.buf_hist = ft_strjoin(tmp, list_elem);
	ft_putstr(main_data.buf_hist);
	main_data.cursor_place = ft_strlen(main_data.buf_hist);
	main_data.key_amount = main_data.cursor_place;
	free(tmp);
	main_data.current_tab = 0;
	main_data.buf_flag = 1;
}

void	is_buff_case(char **list_files, int len, char **list_elem, int i)
{
	int	z;

	if (check_list_file(list_files, len))
	{
		write(1, "\a", 1);
		main_data.current_tab = 0;
		safe_free(main_data.part);
		main_data.part = NULL;
	}
	else
	{
		z = 0;
		*list_elem = choose_list_elem(list_files, len, *list_elem, z);
		autocomplete(*list_elem, i);
	}
}

void	if_zero_current_tab(void)
{
	if (!main_data.current_tab)
	{
		if (!main_data.buf_flag)
		{
			safe_free(main_data.old_buf_hist);
			main_data.old_buf_hist = ft_strdup(main_data.buf_hist);
		}
		main_data.current_tab = 2;
	}
}
