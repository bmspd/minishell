#include "../includes/minishell.h"

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
	if (!home)
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
		return ;
}

void	go_to_direction(t_cmd	*cmd, t_envp *list_envp)
{
	char	*path_dir;

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
	if (chdir(path_dir) == -1)
	{
		print_error("cd", path_dir);
		return ;
	}
	reg_transit(list_envp);
}
