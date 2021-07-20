#include "../includes/minishell.h"

void space(char *str, int *i, int *j)
{
	char *tmp;

	tmp = ft_substr(str, *j, *i - *j);
	main_data.counter++;
	if (ft_strncmp("", tmp, 1) || (!ft_strncmp("", tmp, 1) && main_data.null_flag))
		fill_commands(tmp, main_data.counter);
	else
		fill_commands(NULL, main_data.counter);

	while (str[*i] == ' ')
		(*i)++;
	*j = *i;
	if ((str[*i] == '<' && str[*i + 1] == '<'))
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
