#include "../includes/minishell.h"

char	*get_pwd(void)
{
	char	*pwd;
	char	*chek;
	int		nb;

	// nb = ft_strlen(oldvalue);
	nb = 100;
	pwd = ft_calloc(sizeof(char), nb); //Защетить malloc
	chek = getcwd(pwd, nb);
	nb += 255;
	while (!chek)
	{

		free(pwd);
		pwd = ft_calloc(sizeof(char), nb); //Защетить malloc
		chek = getcwd(pwd, nb);
		nb += 255;
	}
	return (pwd);
}

ENV *find_VAR_ENV(ENV *list_envp, char *VAR)
{
	size_t size;

	size = ft_strlen(VAR);
	while (list_envp)
	{
		if(!ft_strncmp(VAR, list_envp->name, size + 1))
			return (list_envp);
		list_envp = list_envp->next;
	}
	return (NULL);
}

void	print_error(char *cmd, char *arg)
{
		char	*error;

		error = strerror(errno);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		write(2, error, ft_strlen(error));
		write(2, ": ", 2);
		write(2, arg, ft_strlen(arg));
		write(2, "\n", 1);
}

void	lastadd_ENV_VAR(ENV *list_envp, ENV *last)
{
	while (list_envp->next)
	{
		list_envp = list_envp->next;
	}
	list_envp->next = last;
}

void	go_to_direction(char *path_dir, ENV *list_envp)
{
	ENV		*pwd;
	ENV		*oldpwd;
	static char	*newpwd;
	static char	*old;

	if(chdir(path_dir) == -1)
	{
		print_error("cd", path_dir);
		return ;
	}

	pwd = find_VAR_ENV(list_envp, "PWD");
	oldpwd = find_VAR_ENV(list_envp, "OLDPWD");

	if(!oldpwd)
	{
		oldpwd = new_envp("OLDPWD=", NULL);
		lastadd_ENV_VAR(list_envp, oldpwd);
	}

	if(oldpwd->value)
		free(oldpwd->value);

	if (pwd)
		{
			old = pwd->value; 
			oldpwd->value = old;
		}
	else
		{
			old = newpwd;
			oldpwd->value = old;
		}
	newpwd = get_pwd();

	if (pwd)
		pwd->value = newpwd;
}

void	print_pwd(void)
{
	char *tmp;

	tmp = get_pwd();
	printf("%s\n", tmp);
	free(tmp);
}

size_t count_arr(char **arr)
{
	size_t i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}