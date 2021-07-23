#include "../includes/minishell.h"
t_rdfile	*last_rdfile(t_rdfile *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	rdfile_add_back(t_rdfile **lst, t_rdfile *new)
{
	t_rdfile	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = last_rdfile(*lst);
	last->next = new;
}
t_rdfile *new_rdfile(char *name_file, int order)
{
	t_rdfile *rdfile;

	rdfile = malloc(sizeof(t_rdfile));
	if (!rdfile)
		exit(42);
	rdfile->name_file = name_file;
	rdfile->order = order;
	rdfile->next = NULL;
	return (rdfile);
}

void	free_rdfile(t_rdfile *rdfile)
{
	t_rdfile	*tmp;

	while (rdfile)
	{
		tmp = rdfile->next;
		free(rdfile);
		rdfile = tmp;
	}
}