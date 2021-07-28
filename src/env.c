#include "../includes/minishell.h"

void	env(t_envp *list, int fd)
{
	while (list)
	{
		if (ft_strchr(list->name, '='))
		{
			write(fd, list->name, ft_strlen(list->name));
			write(fd, list->value, ft_strlen(list->value));
			write(fd, "\n", 1);
		}
		list = list->next;
	}
}

void	iter_shlvl(t_envp **list_envp)
{
	t_envp	*shlvl;
	int		number;

	number = 1;
	shlvl = find_var_envp(*list_envp, "SHLVL=");
	if (shlvl)
	{
		number = ft_atoi(shlvl->value) + 1;
		free(shlvl->value);
		shlvl->value = NULL;
		shlvl->value = ft_itoa(number);
	}
	else
	{
		shlvl = new_envp("SHLVL", NULL);
		free(shlvl->value);
		shlvl->value = ft_strdup("1");
		lastadd_envp(*list_envp, shlvl);
	}
}
