#include "../includes/minishell.h"

static t_envp *make_copy_envp(void)
{
	t_envp *tmp;
	t_envp *head;
	t_envp *p;

	tmp = main_data.list_envp;
	if (tmp == NULL)
		return (NULL);
	head = malloc(sizeof(t_envp *));
	if (!head)
		exit(42);
	head->name = ft_strdup(tmp->name);
	head->value = ft_strdup(tmp->value);
	p = head;
	tmp = tmp->next;
	while (tmp)
	{
		if (!ft_strncmp("_=", tmp->name, 3))
		{
			tmp = tmp->next;
			continue;
		}
		p->next = malloc(sizeof(t_envp));
		if (!p->next)
			exit(42);
		p = p->next;
		p->name = ft_strdup(tmp->name);
		p->value = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	p->next = NULL;
	return (head);
}

static t_envp *sort_envp(t_envp *head)
{
	t_envp *tmp;
	t_envp *tmp1;
	char *tmp_name;
	char *tmp_value;
	if (!head)
		return (NULL);
	tmp = head;
	while (tmp)
	{
		tmp1 = tmp->next;
		while (tmp1)
		{
			if (ft_strncmp(tmp->name, tmp1->name, ft_strlen(tmp->name) + 1) > 0)
			{
				tmp_name = tmp->name;
				tmp_value = tmp->value;
				tmp->name = tmp1->name;
				tmp->value = tmp1->value;
				tmp1->value = tmp_value;
				tmp1->name = tmp_name;
			}
			tmp1 = tmp1->next;
		}
		tmp = tmp->next;
	}
	return (head);
}

void	print_export(int fd)
{
	t_envp *copy;
	t_envp *tmp;

	copy = make_copy_envp();
	copy = sort_envp(copy);
	tmp = copy;
	while (tmp)
	{
		printf("|%s|%s|\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}

	//printf("print\n");
}

void	export(t_cmd *cmd, int fd)
{
	char	*check;
	t_envp	*tmp;
	char	*name_var;

	if (!cmd->arg[1])
	{
		print_export(fd);
		return ;
	}
	check = ft_strchr(cmd->arg[1], '=');
	if(check)
	{
		name_var = ft_substr(cmd->arg[1], 0, check - cmd->arg[1]);
		tmp = find_var_envp(main_data.list_envp, name_var);
		free(name_var);
		if (!tmp)
		{
			tmp = new_envp(cmd->arg[1], NULL);
			lastadd_envp(main_data.list_envp, tmp);
		}
		else
		{
			free(tmp->value);
			tmp->value = ft_substr(cmd->arg[1], (check - cmd->arg[1]) + 1, ft_strlen(check));
		}
	}
	else
	{
		tmp = find_var_envp(main_data.list_envp, cmd->arg[1]);
		if (!tmp)
		{
			tmp = new_envp(cmd->arg[1], NULL);
			lastadd_envp(main_data.list_envp, tmp);
		}
	}
	
}