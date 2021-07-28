#include "../includes/minishell.h"

int	open_history(int flag)
{
	char	*filename;
	int		fd;
	char	*full;
	char	*path;

	path = getenv("HOME");
	if (path)
	{
		filename = "/.hist";
		full = ft_strjoin(path, filename);
		fd = open(full, O_CREAT | O_RDWR | flag, S_IRWXU);
		free(full);
	}
	else
	{
		filename = ".hist";
		fd = open(filename, O_CREAT | O_RDWR | flag, S_IRWXU);
	}
	return (fd);
}

void	external_history(void)
{
	char	*line;
	int		fd;
	int		i;
	t_list	*tempo;

	i = 1;
	fd = open_history(0);
	while (i)
	{
		i = get_next_line(fd, 128, &line);
		if (!ft_strlen(line))
		{
			free(line);
			continue ;
		}
		ft_lstadd_back(&g_main_data.history,
			ft_lstnew_history(line, (int)ft_strlen(line)));
		numerate_history(g_main_data.history);
	}
	tempo = g_main_data.history;
	while (tempo)
	{
		tempo = tempo->next;
	}
	close(fd);
}

void	fill_external_history(int fd)
{
	t_list	*tmp;

	tmp = g_main_data.history;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, "\4", 2))
		{
			ft_putstr_fd(tmp->content, fd);
			ft_putchar_fd('\n', fd);
		}
		tmp = tmp->next;
	}
	close(fd);
}
