#include "../includes/minishell.h"

void	error_massage_exec(char *name_file)
{
	char	*str_error;

	write(2, "minishell: ", 12);
	str_error = strerror(errno);
	str_error = ft_strdup(str_error);
	str_error = tolower_str(str_error);
	write(2, str_error, ft_strlen(str_error));
	write(2, ": ", 2);
	write(2, name_file, ft_strlen(name_file));
	write(2, "\n", 1);
	exit(127);
}

char	*check_relative_path(t_cmd *cmd, int flag)
{
	char	*path;
	size_t	size;

	size = ft_strrchr(cmd->name, '/') - cmd->name;
	if (ft_strrchr(cmd->name, '/') < cmd->name)
	{
		if (flag == 2)
		{
			write(2, "minishell: ", 12);
			write(2, cmd->name, ft_strlen(cmd->name));
			write(2, ": command not found\n", 21);
		}
		if (flag == 1)
			exit(127);
		if (flag == 2)
			return (NULL);
	}
	path = cmd->name;
	return (path);
}

char	*get_path(t_cmd *cmd)
{
	char	*path;
	t_envp	*PATH;
	t_envp	*HOME;

	path = NULL;
	if (!cmd->name)
		exit(0);
	PATH = find_var_envp(main_data.list_envp, "PATH");
	HOME = find_var_envp(main_data.list_envp, "HOME");
	if (PATH && HOME)
		path = find_path_cmd(PATH->value, cmd->name, HOME->value);
	return (path);
}

void	exec_cmd(t_cmd *cmd, char **envp)
{
	char *path;

	path = get_path(cmd);
	if (!path)
		path = check_relative_path(cmd, 1);
	if (cmd->in >= 0)
		dup2(cmd->in, 0);
	if (cmd->out >= 0)
		dup2(cmd->out, 1);
	if(execve(path, cmd->arg, envp) == -1)
		error_massage_exec(cmd->name);
}

void	reg_last_exec(t_cmd *cmd, t_block *block)
{
	t_envp	*last_exec;
	char	*path;
	
	last_exec = find_var_envp(main_data.list_envp, "_");
	if (last_exec)
	{
		path = get_path(cmd);
		if (!path)
		{
			path = check_relative_path(cmd, 2);
			if (path)
				path = ft_strdup(path);
		}
		if (path)
		{
			free(last_exec->value);
			last_exec->value = path;
		}
	}
}

int	init_fdpipe(t_block *block, int *fd, int in)
{
	fd[0] = -1;
	fd[1] = -1;
	if(!block)
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
		reg_last_exec(block->cmd, block);
		close(fd[1]);
		pipex(block->next, envp, fd[0]);
	}
	else if(!block->pid)
	{
		close(fd[0]);
		get_fd(block, block->cmd, 0);
		if (exec_builtin(block->cmd))
			exit(0);
		exec_cmd(block->cmd, envp);
	}
	return (0);
}
