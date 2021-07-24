#include "../includes/minishell.h"

int	get_index(char *str, char *check)
{
	if (check && !ft_strncmp("<<", str, ft_strlen(str) + 1))
		return (HEREDOC);
	else if (check && !ft_strncmp("<", str, ft_strlen(str) + 1))
		return (RDFILE);
	else if (check && !ft_strncmp(">>", str, ft_strlen(str) + 1))
		return (WRFILEADD);
	else if (check && !ft_strncmp(">", str, ft_strlen(str) + 1))
		return (WRFILETR);
	else if (check && !ft_strncmp("|", str, ft_strlen(str) + 1))
		return (PIPE);
	return (0);
}

void	init_heredoc(t_heredoc **hdoc, char *stop_word, int order)
{
	t_heredoc *new;
	// int status;
	new = new_heredoc(stop_word, order);
	new->fd = heredoc(new->stop_word);
	// wait(&status);
	heredoc_add_back(hdoc, new);
}

void	init_rdfile(t_rdfile **rdfile, char *name_file, int order)
{
	t_rdfile *new;

	new = new_rdfile(name_file, order);
	rdfile_add_back(rdfile, new);
}

void	init_addfile(t_addfile **addfile, char *name_file, int order)
{
	t_addfile *new;

	new = new_addfile(name_file, order);
	addfile_add_back(addfile, new);
}

void	init_trfile(t_trfile **trfile, char *name_file, int order)
{
	t_trfile *new;

	new = new_trfile(name_file, order);
	trfile_add_back(trfile, new);
}

