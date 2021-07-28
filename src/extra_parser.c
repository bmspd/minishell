#include "../includes/minishell.h"

static int	parser_decision(int last_flag_pipe, t_list *tmp)
{
	if (tmp->commands[0] == NULL)
	{
		if (last_flag_pipe && (!ft_strncmp("<", tmp->flag, 2)
				|| !ft_strncmp("<<", tmp->flag, 3)
				|| !ft_strncmp(">>", tmp->flag, 3)
				|| !ft_strncmp(">", tmp->flag, 2)))
			;
		else if (!ft_strncmp("<", tmp->flag, 2)
			|| !ft_strncmp("<<", tmp->flag, 3)
			|| !ft_strncmp(">>", tmp->flag, 3)
			|| !ft_strncmp(">", tmp->flag, 2))
			;
		else
		{
			return (1);
		}
	}
	return (0);
}

static void	flag_condition(int *tmp_flag, int *last_flag_pipe, t_list *tmp)
{
	if (tmp->flag)
	{
		if (!ft_strncmp(tmp->flag, ";", 2))
			*tmp_flag = 1;
		else
			*tmp_flag = 0;
	}
	if (tmp->flag)
	{
		if (!ft_strncmp(tmp->flag, "|", 2))
			*last_flag_pipe = 1;
		else
			*last_flag_pipe = 0;
	}
}

int	extra_parser(void)
{
	int		last_flag_pipe ;
	int		tmp_flag;
	t_list	*tmp;

	last_flag_pipe = 0;
	tmp_flag = 0;
	tmp = main_data.commands;
	if (ft_lstsize(tmp) == 1 && !tmp->commands[0])
		return (1);
	while (tmp)
	{
		if (tmp->id == ft_lstsize(main_data.commands) - 1 && tmp_flag)
			return (1);
		if (parser_decision(last_flag_pipe, tmp)
			|| !ft_strncmp(";", tmp->flag, 2))
		{
			printf("minishell: syntax error!\n");
			main_data.exit_status = 258;
			return (0);
		}
		flag_condition(&tmp_flag, &last_flag_pipe, tmp);
		tmp = tmp->next;
	}
	return (1);
}
