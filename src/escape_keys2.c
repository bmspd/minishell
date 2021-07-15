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

int	check_list_file(char **list_file, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (!ft_strncmp(main_data.part, list_file[i], ft_strlen(main_data.part)))
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
int	take_word_part(void)
{
	int i;
	i = 0;
	char *part;


	if (!ft_strlen(main_data.buf_hist) || main_data.current_tab)
	{
		//printf("1\n");
		main_data.part = ft_strdup("");
		return 0;
	}
	else if (main_data.buf_hist[ft_strlen(main_data.buf_hist) - 1] == ' ')
	{
		//printf("22\n");
		main_data.part = ft_strdup("");
		return 0;
	}
	else if (main_data.buf_flag)
	{
		//printf("LOL\n");
		int z = (int)ft_strlen(main_data.old_buf_hist);
		while (z)
		{
			if (main_data.old_buf_hist[z] == ' ')
			{
				z++;
				break ;
			}
			z--;
		}
		main_data.part = ft_substr(main_data.old_buf_hist, z, ft_strlen(main_data.old_buf_hist) - z);
		return (z);
	}
	else
	{
		int z = (int)ft_strlen(main_data.buf_hist);
		while (z)
		{
			if (main_data.buf_hist[z] == ' ')
			{
				z++;
				break ;
			}
			z--;
		}
		main_data.part = ft_substr(main_data.buf_hist, z, ft_strlen(main_data.buf_hist) - z);
		return (z);
	}
}


int	escape_tab(char *str)
{
	char **list_files;

	int i;
	static char *list_elem;
//	printf("|%s|\n", list_elem);
//	if (!list_elem)
//		list_elem = ft_strdup("");
	char *tmp;
	i = 0;
	list_files = create_list_file();
	int len = (int)count_arr(list_files);

	i = take_word_part();
	if (!main_data.current_tab)
	{

		main_data.old_buf_hist = ft_strdup(main_data.buf_hist);
		main_data.current_tab = 2;
	}
	if(!ft_strncmp(str, "\t", 2))
	{
		if ((main_data.part && !ft_strncmp(main_data.part, "", 2)) || main_data.current_tab > 2)
//		if (part)
		{
			//printf("LOL\n");
			//free(main_data.buf_hist);
			main_data.part = ft_strdup(list_files[main_data.current_tab]);

			tputs(tgetstr("cr", 0), 1, ft_putint);
			tputs(tgetstr("dl", 0), 1, ft_putint);
			print_title();
			tmp = main_data.buf_hist;
			main_data.buf_hist = ft_strjoin(main_data.old_buf_hist, main_data.part);
//			ft_putstr("I AM HERE");
			ft_putstr(main_data.buf_hist);
			main_data.cursor_place = ft_strlen(main_data.buf_hist);
			main_data.key_amount = main_data.cursor_place;
			free(tmp);
			free(main_data.part);
			main_data.current_tab++;
			if (main_data.current_tab == len)
			{
				main_data.current_tab = 2;
			}
			//main_data.part = ft_strdup("");

		}
		else
		{
			if (check_list_file(list_files, len))
			{
				write(1, "\a", 1);
				main_data.part = ft_strdup("l");
				main_data.current_tab = 0;
			}
			else
			{
				int z = 0;
				int index;
				int length;
				if (!list_elem)
				{
					length = 10;
					index = 0;

				}
				else
				{
					length = ft_strlen(list_elem) + 1;
					index = find_index(list_files, len, list_elem);
					//printf("[%d]\n", index);
					//printf("%s\n", list_files[14]);
				}
				//printf("!%s!", main_data.part);
				while (z < len)
				{
					if (!list_elem && !ft_strncmp(main_data.part, list_files[index], ft_strlen(main_data.part)))
					{
						//printf("lol\n");
						list_elem = ft_strdup(list_files[index]);
						break ;
					}
					else if (!ft_strncmp(main_data.part, list_files[index], ft_strlen(main_data.part))
						&& ft_strncmp(list_files[index], list_elem, length))
					{

						//printf("LOL[%d]:[%d]|%s|\n", z, index, list_elem);
						list_elem = ft_strdup(list_files[index]);
						break ;
					}
					index++;
					if (index == len)
						index = 0;
					z++;
				}
				//printf("--%s--\n", main_data.part);
				tputs(tgetstr("cr", 0), 1, ft_putint);
				tputs(tgetstr("dl", 0), 1, ft_putint);
				print_title();
				//main_data.old_buf_hist = main_data.buf_hist;
				tmp = ft_substr(main_data.buf_hist, 0, i);
				//printf("!%s!\n", tmp);
				//printf("|%s|\n", tmp);
				//printf("?%s?\n", main_data.old_buf_hist);

				main_data.buf_hist = ft_strjoin(tmp, list_elem);
				ft_putstr(main_data.buf_hist);
				main_data.cursor_place = ft_strlen(main_data.buf_hist);
				main_data.key_amount = main_data.cursor_place;
				free(tmp);
				//free(main_data.part);
				//main_data.current_tab++;
//				main_data.part = ft_strdup("l");
				main_data.current_tab = 0;
				main_data.buf_flag = 1;
			}
		}
//		while (list_files[i])
//		{
//			printf("|%s|\n", list_files[i]);
//			i++;
//		}
		return (1);
	}
	return (0);
}
