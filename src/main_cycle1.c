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
	main_data.new_cmd_flag = 0;
	main_data.exit_status = 0;
}

int		get_index_builtin(char	*name)
{
	if (!name)
		return (0);
	if (!ft_strncmp("env", name, ft_strlen("env")))
		return (ENV);
	if (!ft_strncmp("pwd", name, ft_strlen("pwd")))
		return (PWD);
	if (!ft_strncmp("cd", name, ft_strlen("cd")))
		return (CD);
	if (!ft_strncmp("export", name, ft_strlen("export")))
		return (EXPORT);
	if (!ft_strncmp("echo", name, ft_strlen("echo")))
		return (MYECHO);
	if (!ft_strncmp("unset", name, ft_strlen("unset")))
		return (UNSET);
	return (0);
}

int	ft_overlap(char *s1, char *s2)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen(s2);
	while (i < size)
	{
		if (ft_strchr(s1, s2[i]))
			return (1);
		i++;
	}
	return (0);
}

int	valid_unset(char *arg)
{
	if (ft_overlap(arg, "<>;-=+~?)(\\|") || ft_isdigit(arg[0]))
	{
		write(2, "unset: `", 8);
		write(2, arg, ft_strlen(arg));
		write(2, "' : not a valid identifier", 27);
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}

void	unset(t_cmd *cmd)
{
	int i;
	t_envp	*tmp;

	i = 1;
	while (cmd->arg[i])
	{
		if(valid_unset(cmd->arg[i]))
			break;
		tmp = find_var_envp(main_data.list_envp, cmd->arg[i]);
		if (tmp)
			rem_envp_VAR(&main_data.list_envp, tmp->name);
		i++;
	}
}

int	exec_builtin(t_cmd *cmd) 
{
	int index;

	index = get_index_builtin(cmd->name);
	if (index)
	{
		if (index == ENV)
			env(main_data.list_envp, cmd->out);
		if (index == PWD)
			print_pwd(cmd->out);
		if (index == CD)
			go_to_direction(cmd, main_data.list_envp);
		if (index == UNSET)
			unset(cmd);
		if (index == MYECHO)
			builtin_echo(&cmd->arg[1], cmd->out);
		if (index == EXPORT)
			export(cmd, cmd->out);
		return (1);
	}
	return (0);
}

void	one_cmd(t_block *block)
{
	pid_t	pid;
	int status;

	if(get_fd(block, block->cmd, 0))
		return ;
	if(exec_builtin(block->cmd))
		return ;
	if (!block->cmd->name)
		return ;
	pid = fork();
	if (pid == -1)
		crash();
	if (pid)
		reg_last_exec(block->cmd, block, 1);
	if (!pid)
		exec_cmd(block->cmd, convert_list_in_arr(main_data.list_envp));
	wait(&status);
	main_data.exit_status = WEXITSTATUS(status);
}

void	kill_childprocess(t_block *block)
{
	while (block)
	{
		if (block->pid)
			kill(block->pid, SIGKILL);
		block = block->next;
	}
}

void	wait_child(t_block *block)
{
	int	status;
	int	i;

	while (block)
	{
		i = (-1 == waitpid(block->pid, &status, 0));
		if (!i)
		{
			main_data.exit_status = WEXITSTATUS(status);
			if (main_data.exit_status == 130)
			{
				kill_childprocess(block);
				break ;
			}
			block = block->next;
		}
	}
}

void	read_block(char **elements, char **help_elements)
{
	t_block	*block;
	char	**envp;

	block = create_pipe_block(elements, help_elements);;
	if (!block)
		return ;
	if (block->next)
	{
		envp = convert_list_in_arr(main_data.list_envp);
		if (pipex(block, envp, STDIN) != -1)
			wait_child(block);
		else
			kill_childprocess(block);
		free_arr(envp, count_arr(envp));
	}
	else
		one_cmd(block);
	free_block(block);
}

void	command_launcher(void)
{
	char	**elements;
	char	**help_elements;
	int		len;


	elements = list_to_char();
	help_elements = list_to_help_char();
	set_terminal(0);
	read_block(elements, help_elements);
	set_terminal(1);
	len = (int)count_arr(elements);
	free_arr(elements, len);
	free_arr(help_elements, len);
}
