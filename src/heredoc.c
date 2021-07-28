#include "../includes/minishell.h"

void	sigint(int a)
{
	if (a == SIGINT)
		exit(1);
	if (a == SIGQUIT)
		return ;
}

void	heredoc_write(char *stop_word, int *fd)
{
	int		tumbler;
	char	*buf;

	g_main_data.term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &g_main_data.term);
	tgetent(0, g_main_data.term_name);
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigint);
	tumbler = 1;
	while (tumbler)
	{
		write(1, "> ", 2);
		if (!get_next_line(0, 256, &buf))
			exit (EXIT_SUCCESS);
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

int	close_crash_heredoc(int flag, int *fd, int status)
{
	if (flag == 1)
		perror("minishell");
	if (flag == 2)
	{
		close(fd[1]);
		close(fd[0]);
		g_main_data.exit_status = WEXITSTATUS(status);
		set_terminal(0);
	}
	return (-1);
}

int	heredoc(char *stop_word)
{
	pid_t	heredoc;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
		return (close_crash_heredoc(1, NULL, 0));
	heredoc = fork();
	if (heredoc == -1)
		crash();
	signal(SIGQUIT, sigint);
	waitpid(heredoc, &status, 0);
	if (WEXITSTATUS(status) == 1)
		return (close_crash_heredoc(2, fd, status));
	if (!heredoc)
	{
		close(fd[0]);
		heredoc_write(stop_word, fd);
	}
	close(fd[1]);
	return (fd[0]);
}
