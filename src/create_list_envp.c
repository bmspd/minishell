#include "../includes/minishell.h"

void	free_VAR(t_envp *ptr)
{
	if (ptr->name)
		free(ptr->name);
	ptr->name = NULL;
	if (ptr->value)
		free(ptr->value);
	ptr->value = NULL;
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	rem_envp_VAR(t_envp **list_envp, char *VAR)
{
	t_envp	*tmp;
	t_envp	*tmp2;

	tmp = NULL;
	tmp2 = *list_envp;
	if (!ft_strncmp(VAR, (*list_envp)->name, ft_strlen((*list_envp)->name)))
	{
		tmp = *list_envp;
		(*list_envp) = (*list_envp)->next;
		free_VAR(tmp);
		return ;
	}
	while (tmp2)
	{
		if (!tmp2->next)
			return ;
		if (!ft_strncmp(VAR, tmp2->next->name, ft_strlen(tmp2->next->name)))
			break ;
		tmp2 = tmp2->next;
	}
	tmp = tmp2->next;
	tmp2->next = tmp2->next->next;
	free_VAR(tmp);
}

t_envp	*new_envp(char	*env, t_envp	*old)
{
	t_envp		*new_env;
	char		*tmp;
	size_t		size;

	new_env = malloc_x(sizeof(t_envp));
	tmp = ft_strchr(env, '=');
	if (tmp)
		size = (tmp - env) + 1;
	else
		size = ft_strlen(env);
	new_env->name = ft_substr(env, 0, size);
	tmp = ft_strchr(env, '=');
	if (tmp)
		new_env->value = ft_strdup(tmp + 1);
	else
		new_env->value = ft_strdup("");
	if (old)
		old->next = new_env;
	new_env->next = NULL;
	return (new_env);
}

t_envp	*create_list_envp(char **envp)
{
	t_envp	*list_envp;
	t_envp	*tmp;
	int		i;

	list_envp = NULL;
	i = 0;
	if (envp[i])
	{
		list_envp = new_envp(envp[i], NULL);
		tmp = list_envp;
		i++;
	}
	while (envp[i])
	{
		tmp->next = new_envp(envp[i], tmp);
		tmp = tmp->next;
		i++;
	}
	check_envp(&list_envp);
	iter_shlvl(&list_envp);
	return (list_envp);
}
