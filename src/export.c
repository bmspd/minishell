#include "../includes/minishell.h"


void	print_export(int fd)
{
	(void)fd;
	printf("print\n");
}

void	export(t_cmd *cmd, int fd)
{
	char	*check;
	t_envp	*tmp;
	char	*name_var;

	if (!cmd->arg[1])
	{
		print_export(fd);
		return ;
	}
	check = ft_strchr(cmd->arg[1], '=');
	if(check)
	{
		name_var = ft_substr(cmd->arg[1], 0, check - cmd->arg[1]);
		tmp = find_var_envp(main_data.list_envp, name_var);
		free(name_var);
		if (!tmp)
		{
			tmp = new_envp(cmd->arg[1], NULL);
			lastadd_envp(main_data.list_envp, tmp);
		}
		else
		{
			free(tmp->value);
			tmp->value = ft_substr(cmd->arg[1], (check - cmd->arg[1]) + 1, ft_strlen(check));
		}
	}
	else
	{
		tmp = find_var_envp(main_data.list_envp, cmd->arg[1]);
		if (!tmp)
		{
			tmp = new_envp(cmd->arg[1], NULL);
			lastadd_envp(main_data.list_envp, tmp);
		}
	}
	
}