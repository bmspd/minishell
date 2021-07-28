#include "../includes/minishell.h"

char	*get_path(t_cmd *cmd, int flag)
{
	char	*path;
	t_envp	*PATH;
	t_envp	*HOME;

	path = NULL;
	if (!cmd->name && flag == 2)
		exit(0);
	if (!cmd->name && flag == 1)
		return (NULL);
	PATH = find_var_envp(main_data.list_envp, "PATH");
	HOME = find_var_envp(main_data.list_envp, "HOME");
	if (PATH && HOME)
		path = find_path_cmd(PATH->value, cmd->name, HOME->value);
	return (path);
}

void	exec_cmd(t_cmd *cmd, char **envp)
{
	char	*path;

	path = get_path(cmd, 2);
	if (!path)
		path = check_relative_path(cmd, 1);
	if (cmd->in >= 0)
		dup2(cmd->in, 0);
	if (cmd->out >= 0)
		dup2(cmd->out, 1);
	if (execve(path, cmd->arg, envp) == -1)
		error_massage_exec(cmd->name);
}

int	init_fdpipe(t_block *block, int *fd, int in)
{
	fd[0] = -1;
	fd[1] = -1;
	if (!block)
	{
		if (in > 2)
			close(in);
		return (0);
	}
	block->cmd->in = in;
	if (block->next)
	{
		if (pipe(fd) == -1)
			return (-1);
		block->cmd->out = fd[1];
	}
	return (1);
}

void	crash(void)
{
	perror("minishell");
	set_terminal(0);
	kill(0, SIGKILL);
}

int	pipex(t_block *block, char **envp, int in)
{
	int	fd[2];
	int	flag;

	flag = init_fdpipe(block, fd, in);
	if (flag != 1)
		return (flag);
	block->pid = fork();
	if (block->pid == -1)
		crash();
	if (block->pid)
	{
		if (!get_index_builtin(block->cmd->name))
			reg_last_exec(block->cmd, block, 1);
		close(fd[1]);
		flag = pipex(block->next, envp, fd[0]);
	}
	else if (!block->pid)
	{
		close(fd[0]);
		if (get_fd(block, block->cmd, 0))
			exit(1);
		if (exec_builtin(block->cmd))
			exit(0);
		exec_cmd(block->cmd, envp);
	}
	return (flag);
}
