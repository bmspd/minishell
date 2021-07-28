#include "../includes/minishell.h"

t_envp	*find_var_envp(t_envp *list_envp, char *VAR)
{
	size_t	size;

	while (list_envp)
	{
		if (!ft_strchr(list_envp->name, '='))
			size = ft_strlen(list_envp->name) + 1;
		else
			size = ft_strlen(list_envp->name) - 1;
		if (!ft_strncmp(VAR, list_envp->name, size))
			return (list_envp);
		list_envp = list_envp->next;
	}
	return (NULL);
}

void	lastadd_envp(t_envp *list_envp, t_envp *last)
{
	while (list_envp->next)
	{
		list_envp = list_envp->next;
	}
	list_envp->next = last;
}

t_envp	*create_oldpwd(t_envp *oldpwd, t_envp *list_envp)
{
	if (!oldpwd)
	{
		oldpwd = new_envp("OLDPWD=", NULL);
		lastadd_envp(list_envp, oldpwd);
	}
	if (!ft_strchr(oldpwd->name, '='))
	{
		free(oldpwd->name);
		oldpwd->name = ft_strdup("OLDPWD=");
	}
	if (oldpwd->value)
		free(oldpwd->value);
	return (oldpwd);
}

t_envp	*rename_pwd(t_envp *pwd)
{
	if (pwd && !ft_strchr(pwd->name, '='))
	{
		free(pwd->name);
		pwd->name = ft_strdup("PWD=");
	}
	return (pwd);
}
