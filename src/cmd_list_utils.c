#include "../includes/minishell.h"

void	fill_id(t_list **head)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *head;
	while (tmp)
	{
		(tmp)->id = i;
		i++;
		tmp = tmp->next;
	}
}

void	init_commands(void)
{
	t_list	*tmp;

	tmp = main_data.commands;
	while (tmp)
	{
		if (tmp->id == main_data.flag1)
			break ;
		tmp = tmp->next;
	}
	tmp->commands = malloc_x(sizeof (char *) * 1);
	tmp->commands[0] = NULL;
	tmp->flag = NULL;
}

void	fill_commands(char *cmd, int cntr)
{
	int i = 0;
	t_list *tmp = main_data.commands;
	while (tmp)
	{
		if (tmp->id == main_data.flag1)
			break ;
		tmp = tmp->next;
	}
	char **new = malloc_x(sizeof(char *) * (cntr + 1));
	while(tmp->commands[i])
	{
		new[i] = ft_strdup(tmp->commands[i]);
		free(tmp->commands[i]);
		i++;
	}
	free(tmp->commands[i]);
	if (cmd)
	{

		new[i] = ft_strdup(cmd);
		//free(cmd);
	}
	else
		new[i] = NULL;
	i++;
	new[i] = NULL;
	free(tmp->commands);
	tmp->commands = new;
}

void	fill_flag(char *flag)
{
	t_list	*tmp = main_data.commands;
	while (tmp)
	{
		if (tmp->id == main_data.flag1)
			break ;
		tmp = tmp->next;
	}
	tmp->flag = ft_strdup(flag);

}