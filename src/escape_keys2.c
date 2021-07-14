#include "../includes/minishell.h"

int escape_ctrl(char *str)
{
	if (str[0] == 12)
	{
		tputs(tgetstr("cl", 0), 1, ft_putint);
		print_title();
		free(main_data.buf_hist);
		main_data.buf_hist = ft_strdup("");
		main_data.cursor_place = 0;
		main_data.history_id = -1;
		return (1);
	}
	return (0);
}

char *take_word_part(void)
{
	int i;
	i = 0;
	char *part;
	if (!ft_strlen(main_data.buf_hist))
	{
		part = ft_strdup("");
		return (part);
	}
//	while(main_data.buf_hist[i])
//	{
//		;
//	}
	return (0);
}

int	escape_tab(char *str)
{
	char **list_files;

	char *part;
	int i;

	i = 0;
	list_files = create_list_file();
	int len = (int)count_arr(list_files);
	if(!ft_strncmp(str, "\t", 2))
	{
		//part = take_word_part();
		if (!ft_strncmp(main_data.buf_hist, "", 2) || main_data.current_tab != 2)
		{
			free(main_data.buf_hist);
			main_data.buf_hist = ft_strdup(list_files[main_data.current_tab]);
			tputs(tgetstr("dl", 0), 1, ft_putint);
			tputs(tgetstr("cr", 0), 1, ft_putint);
			print_title();
			ft_putstr(main_data.buf_hist);
			main_data.current_tab++;
			if (main_data.current_tab == len)
			{
				main_data.current_tab = 2;
				main_data.buf_hist = ft_strdup("");
			}

		}
		else
			printf("ZERO\n");
//		while (list_files[i])
//		{
//			printf("|%s|\n", list_files[i]);
//			i++;
//		}
		return (1);
	}
	return (0);
}
