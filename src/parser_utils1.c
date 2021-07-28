#include "../includes/minishell.h"

static char	*unsuccess_search(char *tmp, char *str, int j)
{
	char	*tmp2;
	char	*tmp3;

	tmp2 = ft_substr(str, 0, j);
	tmp3 = ft_substr(str, j + ft_strlen(tmp) + 1,
			ft_strlen(str) - ft_strlen(tmp));
	free(str);
	str = ft_strjoin(tmp2, tmp3);
	free(tmp);
	free(tmp2);
	free(tmp3);
	return (str);
}

static char	*success_search(char *tmp, char *str, int j, t_envp *search)
{
	char	*tmp2;
	char	*tmp3;

	tmp2 = ft_substr(str, 0, j);
	tmp3 = ft_substr(str, j + ft_strlen(tmp) + 1,
			ft_strlen(str) - ft_strlen(tmp));
	free(tmp);
	tmp = ft_strdup(search->value);
	free(str);
	str = ft_strjoin(tmp2, tmp);
	free(tmp2);
	free(tmp);
	tmp = str;
	str = ft_strjoin(str, tmp3);
	free(tmp);
	free(tmp3);
	return (str);
}

int	ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

static char	*empty_dollar(char *str, char *tmp, int i, int j)
{
	char	*tmp1;
	char	*tmp2;

	free(tmp);
	if (str[i] == '?')
	{
		tmp = ft_itoa(main_data.exit_status);
		tmp1 = ft_substr(str, 0, j);
		tmp2 = ft_substr(str, i + 1, ft_strlen(str) - j - 1);
		free(str);
		str = ft_strjoin(tmp1, tmp);
		free(tmp);
		tmp = ft_strjoin(str, tmp2);
		free(str);
		free(tmp2);
		free(tmp1);
		return (tmp);
	}
	return (str);
}

char	*dollar(char *str, int *i)
{
	int			j;
	char		*tmp;
	t_envp		*search;

	j = *i;
	while (str[*i])
	{
		(*i)++;
		if (!ifkey(str[*i]))
			break ;
	}
	tmp = ft_substr(str, j + 1, *i - j - 1);
	if (!ft_strncmp("", tmp, 1))
		return (empty_dollar(str, tmp, *i, j));
	search = find_var_envp(main_data.list_envp, tmp);
	if (search)
	{
		(*i) = j + (int)ft_strlen(search->value);
		return (success_search(tmp, str, j, search));
	}
	else
	{
		(*i) = j;
		return (unsuccess_search(tmp, str, j));
	}
}
