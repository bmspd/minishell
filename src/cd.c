#include "../includes/minishell.h"

char	*get_pwd(void)
{
	char	*pwd;
	char	*chek;
	int		nb;

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

t_envp *find_var_envp(t_envp *list_envp, char *VAR)
{
	size_t size;

	// size = ft_strlen(VAR);
	while (list_envp)
	{
		if(!ft_strncmp(VAR, list_envp->name, ft_strlen(list_envp->name) - 1))
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

void	lastadd_envp(t_envp *list_envp, t_envp *last)
{
	while (list_envp->next)
	{
		list_envp = list_envp->next;
	}
	list_envp->next = last;
}

void	go_to_direction(t_cmd	*cmd, t_envp *list_envp)
{
	t_envp		*pwd;
	t_envp		*oldpwd;
	t_envp		*home;
	static char	*newpwd;
	static char	*old;
	char *path_dir;

	path_dir = cmd->arg[1];

	if (count_arr(cmd->arg) > 2)
	{
		write(2, "cd: too many arguments\n", 24);
		return ;
	}

	if (!path_dir)
	{
		home = find_var_envp(list_envp, "HOME");
		if (home)
			path_dir = home->value;
		chdir(path_dir);
		return ;
	}

	if(chdir(path_dir) == -1)
	{
		print_error("cd", path_dir);
		return ;
	}

	pwd = find_var_envp(list_envp, "PWD");
	oldpwd = find_var_envp(list_envp, "OLDPWD");


	if(!oldpwd)
	{
		oldpwd = new_envp("OLDPWD=", NULL);
		lastadd_envp(list_envp, oldpwd);
	}
	if (!ft_strchr(oldpwd->name, '='))
		{
			free(oldpwd->name);
			oldpwd->name = ft_strdup("OLDPWD=");
		}
	if (pwd && !ft_strchr(pwd->name, '='))
		{
			free(pwd->name);
			pwd->name = ft_strdup("PWD=");
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

void	print_pwd(int fd)
{
	char *tmp;

	tmp = get_pwd();
	write(fd, tmp, ft_strlen(tmp));
	write(fd, "\n", 1);
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