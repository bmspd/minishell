#include "../includes/minishell.h"

int	valid_export(char *arg, char *out)
{
	if (ft_overlap(arg, "<>;-+?~)(\\|") || ft_isdigit(arg[0]))
	{
		write(2, "export : `", 11);
		write(2, out, ft_strlen(out));
		write(2, "' : not a valid identifier", 27);
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}

void	if_check_exp(char *c, char *name_var, t_cmd *k, int *i)
{
	char	*rename;
	t_envp	*t;

	t = find_var_envp(g_main_data.list_envp, name_var);
	free(name_var);
	if (!t)
	{
		t = new_envp(k->arg[*i], NULL);
		lastadd_envp(g_main_data.list_envp, t);
	}
	else
	{
		free(t->value);
		if (!ft_strchr(t->name, '='))
		{
			rename = t->name;
			t->name = ft_strjoin(rename, "=");
			free(rename);
		}
		t->value = ft_substr(k->arg[*i], (c - k->arg[*i]) + 1, ft_strlen(c));
	}
}

void	else_check_exp(t_envp *tmp, t_cmd *cmd, int *i)
{
	tmp = find_var_envp(g_main_data.list_envp, cmd->arg[*i]);
	if (!tmp)
	{
		tmp = new_envp(cmd->arg[*i], NULL);
		lastadd_envp(g_main_data.list_envp, tmp);
	}
}

int	checking(char *check, int *i, t_cmd *cmd)
{
	char	*name_var;

	if (check)
	{
		name_var = ft_substr(cmd->arg[*i], 0, check - cmd->arg[*i]);
		if (valid_export(name_var, cmd->arg[*i]))
			return (1);
		if_check_exp(check, name_var, cmd, i);
	}
	else
	{
		if (valid_export(cmd->arg[*i], cmd->arg[*i]))
			return (1);
		else_check_exp(NULL, cmd, i);
	}
	return (0);
}

void	export(t_cmd *cmd, int fd)
{
	char	*check;
	int		i;

	if (!cmd->arg[1])
		return (print_export(fd));
	i = 1;
	while (cmd->arg[i])
	{
		check = ft_strchr(cmd->arg[i], '=');
		if (checking(check, &i, cmd))
			return ;
		i++;
	}
}
