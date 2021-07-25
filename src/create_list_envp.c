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

void	free_VAR(t_envp *ptr)
{
	free(ptr->name);
	free(ptr->value);
	free(ptr);
}

void	rem_envp_VAR(t_envp **list_envp, char *VAR)
{
	t_envp *tmp;
	t_envp *tmp2;

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
			break;
		tmp2 = tmp2->next;
	}
	tmp = tmp2->next;
	tmp2->next = tmp2->next->next;
	free_VAR(tmp);
}

t_envp	*new_envp(char	*env, t_envp	*old)
{
	t_envp		*new_env;
	char	*tmp;
	size_t	size;

	new_env = malloc(sizeof(t_envp));
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
	if(old)
		old->next = new_env;
	new_env->next = NULL;
	return (new_env);
}

t_envp	*init_list_envp(void)
{
	t_envp *pwd;
	t_envp *shlvl;
	t_envp *last_exec;

	pwd = new_envp("PWD=", NULL);
	free(pwd->value);
	pwd->value = get_pwd();
	shlvl = new_envp("SHLVL=", pwd);
	free(shlvl->value);
	shlvl->value = ft_strdup("1");
	last_exec = new_envp("_=", shlvl);
	free(last_exec->value);
	last_exec->value = ft_strdup("minishell");
	return (pwd);
}

void	iter_shlvl(t_envp **list_envp)
{
	t_envp	*shlvl;
	int		number;

	number = 1;
	shlvl = find_var_envp(*list_envp, "SHLVL");
	if (shlvl)
	{
		number = ft_atoi(shlvl->value) + 1;
		free(shlvl->value);
		shlvl->value = NULL;
		shlvl->value = ft_itoa(number);
	}
	else
	{
		shlvl = new_envp("SHLVL=", NULL);
		free(shlvl->value);
		shlvl->value = ft_strdup("1");
		lastadd_envp(*list_envp, shlvl);
	}
}

t_envp	*create_list_envp(char **envp)
{
	t_envp	*list_envp;
	t_envp	*tmp;
	int i;

	if(!envp[0])
	{
		list_envp = init_list_envp();
		return (list_envp);
	}
	list_envp = NULL;
	i = 0;
	list_envp = new_envp(envp[i], NULL);
	tmp = list_envp;
	i++;
	while (envp[i])
	{
		tmp->next = new_envp(envp[i], tmp);
		tmp = tmp->next;
		i++;
	}	
	iter_shlvl(&list_envp);
	return (list_envp);
}