#include "../includes/minishell.h"

t_heredoc	*last_heredoc(t_heredoc *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	heredoc_add_back(t_heredoc **lst, t_heredoc *new)
{
	t_heredoc	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = last_heredoc(*lst);
	last->next = new;
}

t_heredoc	*new_heredoc(char *stop_word, int order)
{
	t_heredoc *heredoc;

	heredoc = malloc(sizeof(t_heredoc));
	if (!heredoc)
		exit(42);
	heredoc->stop_word = stop_word;
	heredoc->fd = 0;
	heredoc->order = order;
	heredoc->next = NULL;
	return (heredoc);
}

void	free_heredoc(t_heredoc *heredoc)
{
	t_heredoc	*tmp;

	while (heredoc)
	{
		tmp = heredoc->next;
		if (heredoc->fd > 2)
			close(heredoc->fd);
		free(heredoc);
		heredoc = tmp;
	}
}