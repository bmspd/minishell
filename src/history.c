#include "../includes/minishell.h"

void	numerate_history(t_list *history)
{
	t_list	*tmp;
	int		i;

	tmp = history;
	i = 0;
	while (tmp)
	{
		tmp->id = i;
		tmp = tmp->next;
		i++;
	}
}

void	take_history(void)
{
	t_list	*tmp;

	tmp = g_main_data.history;
	while (tmp)
	{
		if (tmp->id == g_main_data.history_id)
		{
			g_main_data.buf_hist = ft_strdup(tmp->content);
			ft_putstr(tmp->content);
			g_main_data.cursor_place = (int)ft_strlen(g_main_data.buf_hist);
			g_main_data.key_amount = tmp->key_amount;
			return ;
		}
		tmp = tmp->next;
	}
	g_main_data.buf_hist = ft_strdup("");
	g_main_data.cursor_place = 0;
	g_main_data.key_amount = 0;
}

t_list	*ft_lstnew_history(void *content, int amount)
{
	t_list	*new;

	new = (struct s_list *)malloc_x(sizeof(t_list));
	if (new)
	{
		new -> content = content;
		new -> next = NULL;
		new->commands = NULL;
		new->id = 0;
		new->flag = 0;
		new->key_amount = amount;
	}
	return (new);
}
