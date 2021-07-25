#include "../includes/minishell.h"


void	print_export(int fd)
{
	(void)fd;
	printf("print\n");
}

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

void	export(t_cmd *cmd, int fd)
{
	char	*check;
	t_envp	*tmp;
	char	*name_var;
	char	*rename;
	int		i;

	if (!cmd->arg[1])
	{
		print_export(fd);
		return ;
	}
	i = 1;
	while (cmd->arg[i])
	{
		printf("%s\n", cmd->arg[i]);
		i++;
	}
	
	i = 1;
	while(cmd->arg[i])
	{
	check = ft_strchr(cmd->arg[i], '=');
	if(check)
	{
		name_var = ft_substr(cmd->arg[i], 0, check - cmd->arg[i]);
		if (valid_export(name_var, cmd->arg[i]))
			return ;
		tmp = find_var_envp(main_data.list_envp, name_var);
		free(name_var);
		if (!tmp)
		{
			tmp = new_envp(cmd->arg[i], NULL);
			lastadd_envp(main_data.list_envp, tmp);
		}
		else
		{
			free(tmp->value);
			if (!ft_strchr(tmp->name, '='))
			{
				rename = tmp->name;
				tmp->name = ft_strjoin(rename, "=");
				free(rename);
			}
			tmp->value = ft_substr(cmd->arg[i], (check - cmd->arg[i]) + 1, ft_strlen(check));
		}
	}
	else
	{
		if (valid_export(cmd->arg[i], cmd->arg[i]))
			return ;
		tmp = find_var_envp(main_data.list_envp, cmd->arg[i]);
		if (!tmp)
		{
			tmp = new_envp(cmd->arg[i], NULL);
			lastadd_envp(main_data.list_envp, tmp);
		}
	}
	i++;
	}
	
}