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

void	exec_cmd(t_cmd *cmd, char **envp)
{
	char *path;
	t_envp *PATH;
	size_t size;
	t_envp *HOME;

	path = NULL;
	if (!cmd->name)
		exit(0);
	PATH = find_var_envp(main_data.list_envp, "PATH");
	HOME = find_var_envp(main_data.list_envp, "HOME");
	if (PATH && HOME)
	path = find_path_cmd(PATH->value, cmd->name, HOME->value);
	if (!path)
	{
		size = ft_strrchr(cmd->name, '/') - cmd->name;
		if (ft_strrchr(cmd->name, '/') < cmd->name)
		{
			write(2, "minishell: ", 12);
			write(2, cmd->name, ft_strlen(cmd->name));
			write(2, ": command not found\n", 21);
			exit(127);
		}
		path = cmd->name;
	}
	if (cmd->in >= 0)
		dup2(cmd->in, 0);
	if (cmd->out >= 0)
		dup2(cmd->out, 1);
	if(execve(path, cmd->arg, envp) == -1)
		error_massage_exec(cmd->name);
}

int	pipex(t_block *block, char **envp, int in)
{
	int fd[2];

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
	block->pid = fork();
	if (block->pid)
	{
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
		exit(127);
	}
	return (0);
}
