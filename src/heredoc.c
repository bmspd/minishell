#include "../includes/minishell.h"

void	heredoc_write(char *stop_word, int *fd)
{
	int		tumbler;
	char	*buf;


	tumbler = 1;
	while (tumbler)
	{
		write(1, "> ", 2);
		get_next_line(0, 256, &buf);
		tumbler = ft_strncmp(stop_word, buf, ft_strlen(stop_word));
		if (!tumbler)
		{
			free(buf);
			exit (EXIT_SUCCESS);
		}
		write(fd[1], buf, ft_strlen(buf));
		write(fd[1], "\n", 1);
		free(buf);
	}
}

int	heredoc(char *stop_word)
{
	pid_t	heredoc;
	int		fd[2];
	int		status;

	if(pipe(fd) == -1)
	{
		perror("minishell");
		return (-1);
	}
	heredoc = fork();
	if (heredoc == -1)
	{
		perror("minishell");
		kill(0, SIGKILL);
	}
	if (!heredoc)
	{
		close(fd[0]);
		heredoc_write(stop_word, fd);
		exit (-1);
	}
	waitpid(heredoc, &status, 0);
	if (WEXITSTATUS(status))
		return (-1);
	close(fd[1]);
	return (fd[0]);
}

