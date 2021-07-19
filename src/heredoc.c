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
	}
}

int		*heredoc(char *stop_word)
{
	pid_t	heredoc;
	int		*fd;
	int		*status;

	status = malloc(sizeof(int));
	fd = malloc(sizeof(int) * 2);
	if (!fd)
		return (NULL);
	pipe(fd);
	heredoc = fork();
	wait(status);
	if (!heredoc)
	{
		close(fd[0]);
		heredoc_write(stop_word, fd);
		exit (-1);
	}
	if (WEXITSTATUS(status))
	{
		free(fd);
		return (NULL);
	}
	free(status);
	return (fd);
}