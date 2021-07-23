#include "../includes/minishell.h"

static void	heredoc_parse(char *str, char *tmp, int *i, int *j)
{
	free(tmp);
	tmp = ft_substr(str, *i, 2);
	fill_flag(tmp);
	main_data.flag1++;
	ft_lstadd_back(&main_data.commands, ft_lstnew(NULL));
	fill_id(&main_data.commands);
	init_commands();
	main_data.counter = 0;
	(*i) += 2;
	(*j) += 2;
	while (str[*i] == ' ')
		(*i)++;
	*j = *i;
}

static void	other_parse(char *str, char **tmp, int *i, int *j)
{
	free(*tmp);
	*tmp = ft_substr(str, *i, 1);
//	printf("!%s!\n", tmp);
	fill_flag(*tmp);
	main_data.flag1++;
	ft_lstadd_back(&main_data.commands, ft_lstnew(NULL));
	fill_id(&main_data.commands);
	init_commands();
	main_data.counter = 0;
	(*i)++;
	(*j) += 1;
	while (str[*i] == ' ')
		(*i)++;
	*j = *i;
}

void	space(char *str, int *i, int *j)
{
	char	*tmp;

	tmp = ft_substr(str, *j, *i - *j);
	main_data.counter++;
	if (ft_strncmp("", tmp, 1)
		|| (!ft_strncmp("", tmp, 1) && main_data.null_flag))
		fill_commands(tmp, main_data.counter);
	else
		fill_commands(NULL, main_data.counter);
	while (str[*i] == ' ')
		(*i)++;
	*j = *i;
	if ((str[*i] == '<' && str[*i + 1] == '<')
		|| (str[*i] == '>' && str[*i + 1] == '>'))
		heredoc_parse(str, tmp, i, j);
	else if (str[*i] == ';' || str[*i] == '|'
		|| str[*i] == '<' || str[*i] == '>')
		other_parse(str, &tmp, i, j);
	safe_free(tmp);
}

char	*solo_quote(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
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
	(*i)++;
	free(str);
	free(tmp3);
	return (tmp);
}

char	*slash(char *str, int *i)
{
	char	*tmp;
	char	*tmp2;

	(*i)++;
	tmp = ft_substr(str, 0, *i - 1);\
	printf("tmp = |%s|\n", tmp);
	if (!ft_strncmp("", tmp, 2))
	{
		(*i)++;
		free(tmp);
		return (str);
	}
	tmp2 = ft_strdup(str + *i);
	printf("tmp2 = |%s|\n", tmp2);
	free(str);
	str = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	//(*i)++;
	return (str);
}
