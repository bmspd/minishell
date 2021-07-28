#include "../includes/minishell.h"

void	reg_last_exec(t_cmd *cmd, t_block *block, int flag)
{
	t_envp	*last_exec;
	char	*path;

	last_exec = find_var_envp(main_data.list_envp, "_");
	if (last_exec)
	{
		path = get_path(cmd, flag);
		if (!path)
		{
			path = check_relative_path(cmd, 2);
			if (path)
				path = ft_strdup(path);
		}
		if (path)
		{
			free(last_exec->value);
			last_exec->value = path;
		}
	}
}

char	*check_relative_path(t_cmd *cmd, int flag)
{
	char	*path;
	size_t	size;

	if (cmd->name)
		size = ft_strrchr(cmd->name, '/') - cmd->name;
	else if (flag == 2)
		return (NULL);
	else if (flag == 1)
		exit(127);
	if (ft_strrchr(cmd->name, '/') < cmd->name)
	{
		if (flag == 2)
			not_found(cmd);
		if (flag == 1)
			exit(127);
		if (flag == 2)
			return (NULL);
	}
	path = cmd->name;
	return (path);
}
