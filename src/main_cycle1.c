#include "../includes/minishell.h"
#define ENV		1
#define CD		2
#define PWD		3
#define MYECHO	4
#define UNSET	5
#define EXPORT	6

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

int	valid_unset(char *arg)
{
	if (ft_strnstr(arg, "<>;-=+~)(\\|", ft_strlen(arg)))
	{
		write(2, arg, ft_strlen(arg));
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
	int		reg_builtin;
	pid_t	pid;
	int status;

	get_fd(block, block->cmd, 0);
	reg_builtin = exec_builtin(block->cmd);
	if (reg_builtin)
		return ;
	pid = fork();
	if (!pid)
		exec_cmd(block->cmd, convert_list_in_arr(main_data.list_envp));
	wait(&status);
}

void	command_launcher(void)
{
	char	**elements;
	t_block	*block;
	char	**help_elements;
	int		i;
	int		len;

	elements = list_to_char();
	help_elements = list_to_help_char();
	set_terminal(0);
	block = create_pipe_block(elements, help_elements);;
	int status;
	if (block->next)
	{
		pipex(block, convert_list_in_arr(main_data.list_envp), STDIN);
		t_block *tmp = last_block(block);
		while (block)
		{
			i = (-1 == waitpid(block->pid, &status, 0));
			if (!i)
				block = block->next;
		}
		block = tmp;
	}
	else
		one_cmd(block);
	free_block(block);
	set_terminal(1);
	len = (int)count_arr(elements);
	free_arr(elements, len);
	free_arr(help_elements, len);
}
