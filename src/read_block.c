#include "../includes/minishell.h"

void	one_cmd(t_block *block)
{
	pid_t	pid;
	int		status;

	if (get_fd(block, block->cmd, 0))
		return ;
	if (exec_builtin(block->cmd))
		return ;
	if (!block->cmd->name)
		return ;
	pid = fork();
	if (pid == -1)
		crash();
	if (pid)
		reg_last_exec(block->cmd, 1);
	if (!pid)
		exec_cmd(block->cmd, convert_list_in_arr(g_main_data.list_envp));
	wait(&status);
	g_main_data.exit_status = WEXITSTATUS(status);
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

void	close_all_pipe(t_block *block)
{
	while (block)
	{
		if (block->fd_pipe_out > 2)
			close(block->fd_pipe_out);
		if (block->fd_pipe_in > 2)
			close(block->fd_pipe_in);
		block = block->next;
	}
}

void	wait_child(t_block *block)
{
	int	status;
	int	i;
	
	close_all_pipe(block);
	while (block)
	{
		i = (-1 == wait(&status));
		if (!i)
		{
			g_main_data.exit_status = WEXITSTATUS(status);
			if (g_main_data.exit_status == 130)
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

	block = create_pipe_block(elements, help_elements, 0, 1);
	if (!block)
		return ;
	if (block->next)
	{
		envp = convert_list_in_arr(g_main_data.list_envp);
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
