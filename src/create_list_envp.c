#include "../includes/minishell.h"

void	env(ENV *list)
{
	while (list)
	{
			printf("%s", list->name);
			printf("=\"");
			if	(list->value)
				printf("%s", list->value);
			printf("\"\n");
		list = list->next;
	}
}

void	free_VAR(ENV *ptr)
{
	free(ptr->name);
	free(ptr->value);
	free(ptr);
}

void	rem_envp_VAR(ENV **list_envp, char *VAR)
{
	ENV *tmp;
	ENV *tmp2;

	tmp = NULL;
	tmp2 = *list_envp;
	if (!ft_strncmp(VAR, (*list_envp)->name, ft_strlen((*list_envp)->name)))
	{
		printf("Удален %s\n", (*list_envp)->name);
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
	printf("Удален %s\n", tmp2->next->name);
	tmp = tmp2->next;
	tmp2->next = tmp2->next->next;
	free_VAR(tmp);
}

ENV	*new_envp(char	*env, ENV	*old)
{
	ENV		*new_env;
	char	*tmp;

	new_env = malloc(sizeof(ENV));
	tmp = ft_strchr(env, '=');
	new_env->name = ft_substr(env, 0, tmp - env);
	new_env->value = ft_strdup(ft_strchr(env, '=') + 1);
	if(old)
		old->next = new_env;
	new_env->next = NULL;
	return (new_env);
}

ENV	*init_list_envp(void)
{
	ENV *pwd;
	ENV *shlvl;
	ENV *last_exec;

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

void	iter_shlvl(ENV **list_envp)
{
	ENV	*shlvl;
	int		number;

	number = 1;
	shlvl = find_VAR_ENV(*list_envp, "SHLVL");
	if (shlvl)
	{
		number = ft_atoi(shlvl->value) + 1;
		free(shlvl->value);
		shlvl->value = NULL;
		shlvl->value = ft_strdup(ft_itoa(number));
	}
	else
	{
		shlvl = new_envp("SHLVL=", NULL);
		free(shlvl->value);
		shlvl->value = ft_strdup("1");
		lastadd_ENV_VAR(*list_envp, shlvl);
	}
}

ENV	*create_list_envp(char **envp)
{
	ENV	*list_envp;
	ENV	*tmp;
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