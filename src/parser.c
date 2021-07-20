#include "../includes/minishell.h"
#include <sys/stat.h>



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
	free(str);
	str = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	tmp = ft_strjoin(str, tmp3);
	//printf("tmp = %s\n", tmp);
	(*i)++;
	free(str);
	free(tmp3);
	return (tmp);
}

char *slash(char *str, int *i)
{
	char *tmp;
	char *tmp2;

	(*i)++;
	tmp = ft_substr(str, 0, *i - 1);
	if (!ft_strncmp("", tmp, 2))
	{
		(*i)++;
		free(tmp);
		return (str);
	}
	tmp2 = ft_strdup(str + *i);
	free(str);
	str = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	(*i)++;
	return (str);
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
		if (str[*i] == '\\' && (str[*i + 1] == '\"' || str[*i + 1] == '$' || str[*i + 1] == '\\'))
			str = slash(str, i);
		if (str[*i] == '$')
			str = dollar(str, i);
		if (str[*i] == '\"')
			break ;

	}
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


void parser(char *str)
{
	int j;
	int i;
	i = 0;
	j = 0;

	while (str[i] == ' ')
	{
		i++;
		j++;
	}
	while(str[i])
	{

		if (str[i] == ' ' || str[i] == ';' || str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			//printf("SPACE\n");
			space(str, &i, &j);
			main_data.null_flag = 0;
		}
		else if (str[i] == '\'')
		{
			main_data.null_flag = 1;
			str = solo_quote(str, &i);
			i = i - 2;
		}
		else if (str[i] == '\\')
		{
			//printf("SLASH\n");
			str = slash(str, &i);
			i = i - 1;
		}
		else if (str[i] == '\"')
		{
			//printf("DOUBLE\n");
			main_data.null_flag = 1;
			str = double_quote(str, &i);
			i = i - 2;
		}
		else if (str[i] == '$')
		{
			//printf("wtf\n");
			str = dollar(str, &i);
			//i = i - 1;
		}
		else
			i++;
	}
	space(str, &i, &j);
	free(str);
	//return (str);
}

