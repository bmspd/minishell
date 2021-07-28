#include "../includes/minishell.h"

void	add_pwd(t_envp **list_envp)
{
	t_envp	*pwd;


	pwd = new_envp("PWD=", NULL);
	free(pwd->value);
	pwd->value = get_pwd();
	if (!*list_envp)
		*list_envp = pwd;
	else
		lastadd_envp(*list_envp, pwd);
}

void	add_shlvl(t_envp **list_envp)
{
	t_envp	*shlvl;

	shlvl = new_envp("SHLVL=", NULL);
	free(shlvl->value);
	shlvl->value = ft_strdup("0");
	lastadd_envp(*list_envp, shlvl);
}

void	add_last_exec(t_envp **list_envp)
{
	t_envp	*last_exec;

	last_exec = new_envp("_=", NULL);
	free(last_exec->value);
	last_exec->value = ft_strdup("minishell");
	lastadd_envp(*list_envp, last_exec);
}

void	add_oldpwd(t_envp **list_envp)
{
	t_envp	*oldpwd;

	oldpwd = new_envp("OLDPWD", NULL);
	lastadd_envp(*list_envp, oldpwd);
}

void	check_envp(t_envp **list_envp)
{
	t_envp	*pwd;
	t_envp	*shlvl;
	t_envp	*last_exec;
	t_envp	*oldpwd;

	pwd = find_var_envp(*list_envp, "PWD");
	if(!pwd)
		add_pwd(list_envp);
	shlvl = find_var_envp(*list_envp, "SHLVL");
	if (!shlvl)
		add_shlvl(list_envp);
	last_exec = find_var_envp(*list_envp, "_");
	if (!last_exec)
		add_last_exec(list_envp);
	oldpwd = find_var_envp(*list_envp, "OLDPWD");
	if (!oldpwd)
		add_oldpwd(list_envp);
}
