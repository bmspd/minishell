#include "../includes/minishell.h"

char	*left_to_right_quote(char *str, int *i)
{
	while (str[(*i)])
	{
		(*i)++;
		if (str[*i] == '\\' && (str[*i + 1] == '\"'
				|| str[*i + 1] == '$' || str[*i + 1] == '\\'))
			str = slash(str, i);
		if (str[*i] == '$')
			str = dollar(str, i);
		if (str[*i] == '\"')
			break ;
	}
	return (str);
}

char	*double_quote(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	str = left_to_right_quote(str, i);
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	free(str);
	str = ft_strjoin(tmp, tmp2);
	free(tmp);
	tmp = ft_strjoin(str, tmp3);
	free(str);
	free(tmp2);
	free(tmp3);
	(*i)++;
	return (tmp);
}

char	*delete_spaces_behind(char *str)
{
	int		len;
	char	*tmp;

	len = (int)ft_strlen(str) - 1;
	while (str[len] == ' ')
	{
		len--;
	}
	tmp = ft_substr(str, 0, len + 1);
	return (tmp);
}
