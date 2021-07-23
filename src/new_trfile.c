#include "../includes/minishell.h"

t_trfile	*last_trfile(t_trfile *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	trfile_add_back(t_trfile **lst, t_trfile *new)
{
	t_trfile	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = last_trfile(*lst);
	last->next = new;
}

t_trfile *new_trfile(char *name_file, int order)
{
	t_trfile *trfile;

	trfile = malloc(sizeof(t_trfile));
	if (!trfile)
		exit(42);
	trfile->name_file = name_file;
	trfile->order = order;
	trfile->next = NULL;
	return (trfile);
}

void	free_trfile(t_trfile *trfile)
{
	t_trfile	*tmp;

	while (trfile)
	{
		tmp = trfile->next;
		free(trfile);
		trfile = tmp;
	}
}