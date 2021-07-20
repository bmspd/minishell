#include "../includes/minishell.h"
int count_elements(void)
{
    int counter;
    int i;

    counter = 0;
    t_list *tmp = main_data.commands;
    while (tmp)
    {
        i = 0;
        while (tmp->commands[i])
        {
            counter++;
            i++;
        }
        if (tmp->flag)
            counter++;
        tmp = tmp->next;
    }
    return (counter);
}
char **list_to_help_char(void)
{
	int len;
	char **help_elements;
	int i;

	len = count_elements();
	help_elements = malloc(sizeof(char *) * (len + 1));
	len = 0;
	t_list *tmp = main_data.commands;
	while (tmp)
	{
		i = 0;
		while(tmp->commands[i++])
		{
			help_elements[len] = NULL;
			len++;
		}
		if (tmp->flag)
		{
			help_elements[len] = ft_strdup(tmp->flag);
			len++;
		}
		tmp = tmp->next;
	}
	help_elements[len] = NULL;
	return(help_elements);
}

char **list_to_char(void)
{
    int len;
    char **elements;
    int i;

    len = count_elements();
    elements = malloc(sizeof(char *) * (len + 1));
    len = 0;
    t_list *tmp = main_data.commands;
    while (tmp)
    {
        i = 0;
        while(tmp->commands[i])
        {
            elements[len] = ft_strdup(tmp->commands[i++]);
            len++;
        }
        if (tmp->flag)
        {
            elements[len] = ft_strdup(tmp->flag);
            len++;
        }
        tmp = tmp->next;
    }
    elements[len] = NULL;
    return(elements);
}
