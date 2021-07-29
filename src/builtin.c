#include "../includes/minishell.h"

int	get_index_builtin(char	*name)
{
	if (!name)
		return (0);
	if (!ft_strncmp("env", name, ft_strlen("env") + 1))
		return (ENV);
	if (!ft_strncmp("pwd", name, ft_strlen("pwd") + 1))
		return (PWD);
	if (!ft_strncmp("cd", name, ft_strlen("cd") + 1))
		return (CD);
	if (!ft_strncmp("export", name, ft_strlen("export") + 1))
		return (EXPORT);
	if (!ft_strncmp("echo", name, ft_strlen("echo") + 1))
		return (MYECHO);
	if (!ft_strncmp("unset", name, ft_strlen("unset") + 1))
		return (UNSET);
	if (!ft_strncmp("exit", name, ft_strlen("exit") + 1))
		return (EXIT);
	return (0);
}

int	get_output_value(t_cmd *cmd)
{
	if (!cmd->arg[1])
		return (0);
	if (!ft_overlap(cmd->arg[1], "-+0123456789"))
	{
		write(2, "minishell: exit: ", 17);
		write(2, cmd->arg[1], ft_strlen(cmd->arg[1]));
		write(2, ": numeric argument required\n", 29);
		return (255);
	}
	if (count_arr(cmd->arg) > 2)
		return (256);
	return (ft_atoi(cmd->arg[1]) & 255);
}

void	my_exit(t_cmd *cmd)
{
	int	out;

	set_terminal(0);
	write(1, "💔💔💔 \x1b[36msee ya later \x1b[31m↻\x1b[0m\n",
		 ft_strlen("💔💔💔 \x1b[36msee ya later \x1b[31m↻\x1b[0m\n"));
	out = get_output_value(cmd);
	if (out > 255)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return ;
	}
	exit(out);
}

int	exec_builtin(t_cmd *cmd)
{
	int	index;

	index = get_index_builtin(cmd->name);
	if (index)
	{
		if (index == ENV)
			env(g_main_data.list_envp, cmd->out);
		if (index == PWD)
			print_pwd(cmd->out);
		if (index == CD)
			go_to_direction(cmd, g_main_data.list_envp);
		if (index == UNSET)
			unset(cmd);
		if (index == MYECHO)
			builtin_echo(&cmd->arg[1], cmd->out);
		if (index == EXPORT)
			export(cmd, cmd->out);
		if (index == EXIT)
			my_exit(cmd);
		return (1);
	}
	return (0);
}
