#include "../includes/minishell.h"

char	**ft_realloc(char **ptr, size_t size)
{
	char	**new_exemp;
	char	**tmp;

	new_exemp = ft_calloc(sizeof(char *), size + 1);
	if (!new_exemp)
		return (NULL);
	tmp = ft_memcpy(new_exemp, ptr, sizeof(char *) * count_arr(ptr));
	if (tmp)
		new_exemp = tmp;
	free(ptr);
	ptr = NULL;
	return (new_exemp);
}

t_cmd	*new_cmd(char *name)
{
	t_cmd	*cmd;

	cmd = malloc_x(sizeof(t_cmd));
	if (!cmd)
		exit(42);
	cmd->in = 0;
	cmd->out = 1;
	cmd->name = name;
	cmd->arg = ft_calloc(sizeof(char *), 2);
	if (!cmd->arg)
		exit(42);
	cmd->arg[0] = name;
	cmd->env = NULL;
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->in > 2)
		close(cmd->in);
	if (cmd->out > 2)
		close(cmd->out);
	if (!cmd->arg)
		free(cmd->arg);
	free(cmd);
}