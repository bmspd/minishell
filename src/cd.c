#include "../includes/minishell.h"

char	*get_pwd(void)
{
	char	*pwd;
	char	*chek;
	int		nb;

	nb = 100;
	pwd = ft_calloc(sizeof(char), nb);
	if (!pwd)
		exit(42);
	chek = getcwd(pwd, nb);
	nb += 255;
	while (!chek)
	{

		free(pwd);
		pwd = ft_calloc(sizeof(char), nb);
		if (!pwd)
			exit(42);
		chek = getcwd(pwd, nb);
		nb += 255;
	}
	return (pwd);
}

t_envp	*find_var_envp(t_envp *list_envp, char *VAR)
{
	size_t	size;


	while (list_envp)
	{
		if (!ft_strchr(list_envp->name, '='))
			size = ft_strlen(list_envp->name);
		else
			size = ft_strlen(list_envp->name) - 1;
		if(!ft_strncmp(VAR, list_envp->name, size))
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

t_envp	*create_oldpwd(t_envp *oldpwd, t_envp *list_envp)
{
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
	if(oldpwd->value)
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

void	free_and_write_pwd(t_envp *pwd, char *newpwd)
{
	free(pwd->value);
	pwd->value = newpwd;
}

void	rewrite_pwd_oldpwd(t_envp *pwd, t_envp *oldpwd)
{
	static char	*newpwd;
	static char	*old;
	static int	flag;

	if (pwd)
	{
		if (flag)
			free_and_write_pwd(pwd, newpwd);
		old = pwd->value; 
		oldpwd->value = old;
		flag = 0;
	}
	else
	{
		if (!flag)
		newpwd = NULL;
		old = newpwd;
		oldpwd->value = old;
		if (newpwd == NULL)
			flag = 1;
	}
	newpwd = get_pwd();
	if (pwd)
		pwd->value = newpwd;
}

void	reg_transit(t_envp *list_envp)
{
	t_envp		*pwd;
	t_envp		*oldpwd;


	pwd = find_var_envp(list_envp, "PWD");
	oldpwd = find_var_envp(list_envp, "OLDPWD");
	oldpwd = create_oldpwd(oldpwd, list_envp);
	pwd = rename_pwd(pwd);
	rewrite_pwd_oldpwd(pwd, oldpwd);
}

void	go_to_home(t_envp *list_envp)
{
	char	*path_dir;
	t_envp	*home;

	home = find_var_envp(list_envp, "HOME");
	if(!home)
	{
		write(2, "minishell: cd: HOME not set\n", 29);
		return ;
	}
	if (ft_strchr(home->name, '='))
		path_dir = home->value;
	else
	{
		write(2, "minishell: cd: HOME not set\n", 29);
		return ;
	}
	if (path_dir)
	{
		chdir(path_dir);
		reg_transit(list_envp);
	}
	else
		return;
}

void	go_to_direction(t_cmd	*cmd, t_envp *list_envp)
{
	char *path_dir;

	path_dir = cmd->arg[1];
	if (count_arr(cmd->arg) > 2)
	{
		write(2, "cd: too many arguments\n", 24);
		return ;
	}
	if (!path_dir)
	{
		go_to_home(list_envp);
		return ;
	}
	if(chdir(path_dir) == -1)
	{
		print_error("cd", path_dir);
		return ;
	}
	reg_transit(list_envp);
}

void	print_pwd(int fd)
{
	char *tmp;

	tmp = get_pwd();
	write(fd, tmp, ft_strlen(tmp));
	write(fd, "\n", 1);
	free(tmp);
}

size_t	count_arr(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}