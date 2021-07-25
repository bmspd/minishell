#include "../includes/minishell.h"

static int	pipes_squote_slash(char **str, int *i, int *j)
{
	if ((*str)[*i] == ' ' || (*str)[*i] == ';'
		|| (*str)[*i] == '|' || (*str)[*i] == '<' || (*str)[*i] == '>')
	{
		space(*str, i, j);
		main_data.null_flag = 0;
		return (1);
	}
	else if ((*str)[*i] == '\'')
	{
		main_data.null_flag = 1;
		*str = solo_quote(*str, i);
		*i = *i - 2;
		return (2);
	}
	else if ((*str)[*i] == '\\')
	{
		*str = slash(*str, i);
		return (3);
	}
	return (0);
}

static int	dquote_dollar(char **str, int *i, int *j)
{
	if ((*str)[*i] == '\"')
	{
		main_data.null_flag = 1;
		*str = double_quote(*str, i);
		*i = *i - 2;
		return (4);
	}
	else if ((*str)[*i] == '$')
	{
		*str = dollar(*str, i);
		return (5);
	}
	return (0);
}

void	parser(char *str)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (str[i] == ' ')
	{
		i++;
		j++;
	}
	while (str[i])
	{
		if (pipes_squote_slash(&str, &i, &j))
			;
		else if (dquote_dollar(&str, &i, &j))
			;
		else
			i++;
	}
	space(str, &i, &j);
	free(str);
}
