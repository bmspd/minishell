#include "../includes/minishell.h"

char *solo_quote(char *str, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;

	while (str[*i])
	{
		(*i)++;
		if (str[*i] == '\'')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	printf("tmp = %s\n", tmp);
	free(str);
	return (tmp);
}

char *slash(char *str, int *i)
{
	char *tmp;
	char *tmp2;

	tmp = ft_substr(str, 0, *i);
	tmp2 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	free(str);
	(*i)++;
	printf("tmp = %s\n", tmp);
	return (tmp);
}

char	*double_quote(char *str, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;

	while (str[(*i)])
	{
		(*i)++;
		if (str[*i] == '\\' && (str[*i + 1] == '\"' || str[*i + 1] == '$'))
			str = slash(str, i);
		if (str[*i] == '\"')
			break ;

	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	printf("tmp = %s\n", tmp);
	return (tmp);
}
// "", '', \, $, ;, |, >, >>, <
void parser(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '\'')
			str = solo_quote(str, &i);
		if (str[i] == '\\')
			str = slash(str, &i);
		if (str[i] == '\"')
			str = double_quote(str, &i);
		i++;
	}
}


int	main(void)
{
	char *str = ft_strdup("comma'n\\nn'dd000\\'00co\"mm\\\"\"an'dddd'a");

	parser(str);
}

