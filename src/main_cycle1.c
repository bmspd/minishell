#include "../includes/minishell.h"

static int	break_condition(char *str)
{
	if (!ft_strncmp("\4", str, 2) && (!ft_strncmp("\4", str, 2)
			&& !ft_strncmp("", main_data.buf_hist, 2)))
	{
		safe_free(main_data.buf_hist);
		main_data.buf_hist = ft_strdup("\4");
		write(1, "exit\n", 6);
		return (1);
	}
	if (!ft_strncmp("\n", str, 2))
	{
		return (1);
	}
	return (0);
}

void	typing_cycle(void)
{
	char	str[2000];
	int		l;

	while (10)
	{
		l = read(0, str, 2000);
		str[l] = 0;
		if (key_control(str))
			;
		else
		{
			if (ft_strncmp("\4", str, 2))
			{
				write(1, str, l);
				main_data.key_amount++;
				if (ft_strncmp("\n", str, 2))
					symbol_not_enter(str);
			}
		}
		if (break_condition(str))
			break ;
	}
}

void	symbol_not_enter(char *str)
{
	char	*tmp0;
	char	*tmp1;
	char	*tmp2;

	safe_free(main_data.part);
	main_data.part = NULL;
	main_data.current_tab = 0;
	main_data.buf_flag = 0;
	tmp0 = ft_substr(main_data.buf_hist, 0, main_data.cursor_place);
	tmp1 = ft_strjoin(tmp0, str);
	tmp2 = ft_substr(main_data.buf_hist, main_data.cursor_place,
			ft_strlen(main_data.buf_hist) - main_data.cursor_place);
	free(main_data.buf_hist);
	main_data.buf_hist = ft_strjoin(tmp1, tmp2);
	main_data.cursor_place += (int)ft_strlen(str);
	write(1, tmp2, ft_strlen(tmp2));
	cursor_behaviour(tmp2);
	main_data.history_id = -1;
	free(tmp0);
	free(tmp2);
	free(tmp1);
}

void	init_variables(void)
{
	main_data.cursor_place = 0;
	main_data.null_flag = 0;
	main_data.key_amount = 0;
	main_data.buf_hist = NULL;
	main_data.history = NULL;
	main_data.current_tab = 0;
	main_data.part = NULL;
	main_data.buf_flag = 0;
	main_data.history_id = -1;
}

void	command_launcher(void)
{
	char	**elements;
	char	**help_elements;
	int		i;
	int		len;

	elements = list_to_char();
	help_elements = list_to_help_char();
	i = 0;
	while (elements[i])
	{
		printf("|%s|[%s]\n", elements[i], help_elements[i]);
		i++;
	}
	set_terminal(0);
				
	t_block *block;
	block = create_pipe_block(elements);
	int status;
	// wait(&status);
	pipex(block, convert_list_in_arr(main_data.list_envp), STDIN);
	i = 0;
	// int size = count_block(block);
	// printf("%d\n", size);
	t_block *tmp = block;
	while (block)
	{
		i = (-1 == waitpid(block->pid, &status, 0));
		if (!i)
			block = block->next;
	}
	//read_cmd(main_data.commands, &list_envp);	//функция запуска комманд <-----где-то здесь должна быть
	set_terminal(1);
	len = (int)count_arr(elements);
	free_arr(elements, len);
	free_arr(help_elements, len);
}
