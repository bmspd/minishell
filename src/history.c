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

	tmp = main_data.history;
	while (tmp)
	{
		if (tmp->id == main_data.history_id)
		{
			main_data.buf_hist = ft_strdup(tmp->content);
			ft_putstr(tmp->content);
			main_data.cursor_place = (int)ft_strlen(main_data.buf_hist);
			main_data.key_amount = tmp->key_amount;
			return ;
		}
		tmp = tmp->next;
	}
	main_data.buf_hist = ft_strdup("");
	main_data.cursor_place = 0;
	main_data.key_amount = 0;
}
