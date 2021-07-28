#include "../includes/minishell.h"
void	free_arr(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		i++;
	}
	free(arr);
}

int	count_list(t_envp *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

char	*convert_in_str(char *s1, char *s2)
{
	char	*out;

	out = ft_strjoin(s1, s2);
	return (out);
}

int	minus_count(int count, t_envp *tmp)
{
	while (tmp)
	{
		if (!ft_strchr(tmp->name, '='))
			count--;
		tmp = tmp->next;
	}
	return (count);
}

char	**convert_list_in_arr(t_envp *list_envp)
{
	int		count;
	char	**envp;
	int		i;

	count = count_list(list_envp);
	count = minus_count(count, list_envp);
	envp = malloc_x(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		if (ft_strchr(list_envp->name, '='))
		{
			envp[i] = convert_in_str(list_envp->name, list_envp->value);
			i++;
		}
		list_envp = list_envp->next;
	}
	envp[i] = NULL;
	return (envp);
}
