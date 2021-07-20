#include "../includes/minishell.h"
#include <sys/stat.h>



char *dollar(char *str, int *i, char **env);
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
	tmp2 = ft_strdup(str + *i);
	free(str);
	str = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	(*i)++;
	return (str);
}

char	*double_quote(char *str, int *i, char **env)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;

	while (str[(*i)])
	{
		(*i)++;
		// в двойных кавычках
		// бэкслэш экранирует только двойную кавычку, доллар или самого себя!
		if (str[*i] == '\\' && (str[*i + 1] == '\"' || str[*i + 1] == '$' || str[*i + 1] == '\\'))
			str = slash(str, i);
		if (str[*i] == '$')
			str = dollar(str, i, env);
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
	//printf("loltmp = %s\n", tmp);
	(*i)++;
	return (tmp);
}

int ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}
char *dollar(char *str, int *i, char **env)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;
	int z = 0;
	int flag = 0;
	while (str[*i])
	{
		(*i)++;
		if (!ifkey(str[*i]))
			break ;
	}
//	if (*i == j)
//		return (str);

	tmp = ft_substr(str, j + 1, *i - j - 1);
	//printf("[%s]\n", tmp);
    ENV *search = find_VAR_ENV(main_data.list_envp, tmp);
    if (search)
    {
        tmp2 = ft_substr(str, 0, j);
       // printf("??%s??\n", tmp2);
        tmp3 = ft_substr(str, j + ft_strlen(tmp) + 1, ft_strlen(str) - ft_strlen(tmp));
        free(tmp);
        tmp = ft_strdup(search->value);

       // printf("??%s??\n", tmp3);
        free(str);
        str = ft_strjoin(tmp2, tmp);
        free(tmp2);
        free(tmp);
        tmp = str;
        str = ft_strjoin(str, tmp3);
        free(tmp);
        free(tmp3);
        (*i) = j + ft_strlen(search->value);
        return (str);
    }
    else
    {
        tmp2 = ft_substr(str, 0, j);
       // printf("??%s??[%d]\n", tmp2, j);
        tmp3 = ft_substr(str, j + ft_strlen(tmp) + 1, ft_strlen(str) - ft_strlen(tmp));
    //    printf("??%s??[%d]\n", tmp3,j + ft_strlen(tmp));
        free(str);
        str = ft_strjoin(tmp2, tmp3);
        free(tmp);
        free(tmp2);
        free(tmp3);
        (*i) = j;
        return (str);
    }
}

void space(char *str, int *i, int *j)
{
	char *tmp;

	tmp = ft_substr(str, *j, *i - *j);

	main_data.counter++;
	if (strcmp(tmp, "") || (!strcmp(tmp,"") && main_data.null_flag))
		fill_commands(tmp, main_data.counter);
	else
		fill_commands(NULL, main_data.counter);

	while (str[*i] == ' ')
		(*i)++;
	*j = *i;
	if ((str[*i] == '<' && str[*i + 1] == '<') || (str[*i] == '>' && str[*i] == '>'))
	{
		free(tmp);
		tmp = ft_substr(str, *i, 2);
		fill_flag(tmp);
		main_data.flag1++;
		ft_lstadd_back(&main_data.commands, ft_lstnew(NULL));
		fill_id(&main_data.commands);
		init_commands();
		main_data.counter = 0;
		(*i)+= 2;
		(*j)+= 2;
		while (str[*i] == ' ')
			(*i)++;
		*j = *i;
	}
	else if (str[*i] == ';' || str[*i] == '|' || str[*i] == '<' || str[*i] == '>')
	{
		free(tmp);
		tmp = ft_substr(str, *i, 1);

		// printf("flag = %s\n", tmp);
		fill_flag(tmp);
		main_data.flag1++;
		ft_lstadd_back(&main_data.commands, ft_lstnew(NULL));
		fill_id(&main_data.commands);
		init_commands();
		main_data.counter = 0;
		(*i)++;
		(*j)+= 1;
		while (str[*i] == ' ')
			(*i)++;
		*j = *i;
	}
	free(tmp);
}
// "", '', \, $, ;, |, >, >>, < ' '
void parser(char *str, char **env)
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
			str = double_quote(str, &i, env);
			i = i - 2;
		}
		else if (str[i] == '$')
		{
			//printf("wtf\n");
			str = dollar(str, &i, env);
			//i = i - 1;
		}
		else
			i++;
	}

	space(str, &i, &j);
	free(str);
	//return (str);
}

