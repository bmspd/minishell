#include "../includes/minishell.h"

int	ft_overlap(char *s1, char *s2)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen(s2);
	while (i < size)
	{
		if (ft_strchr(s1, s2[i]))
			return (1);
		i++;
	}
	return (0);
}

int	valid_unset(char *arg)
{
	if (ft_overlap(arg, "<>;-=+~?)(\\|") || ft_isdigit(arg[0]))
	{
		write(2, "unset: `", 8);
		write(2, arg, ft_strlen(arg));
		write(2, "' : not a valid identifier", 27);
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}

void	unset(t_cmd *cmd)
{
	int		i;
	t_envp	*tmp;

	i = 1;
	while (cmd->arg[i])
	{
		if (valid_unset(cmd->arg[i]))
			break ;
		tmp = find_var_envp(main_data.list_envp, cmd->arg[i]);
		if (tmp)
			rem_envp_VAR(&main_data.list_envp, tmp->name);
		i++;
	}
}
