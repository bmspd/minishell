#include "../includes/minishell.h"

t_addfile	*last_addfile(t_addfile *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	addfile_add_back(t_addfile **lst, t_addfile *new)
{
	t_addfile	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = last_addfile(*lst);
	last->next = new;
}

t_addfile	*new_addfile(char *name_file, int order)
{
	t_addfile	*addfile;

	addfile = malloc_x(sizeof(t_addfile));
	if (!addfile)
		exit(42);
	addfile->name_file = name_file;
	addfile->order = order;
	addfile->next = NULL;
	return (addfile);
}

void	free_addfile(t_addfile	*addfile)
{
	t_addfile	*tmp;

	while (addfile)
	{
		tmp = addfile->next;
		free(addfile);
		addfile = tmp;
	}
}
