#include "../includes/minishell.h"

static t_envp *make_copy_envp(void)
{
	t_envp *tmp;
	t_envp *head;
	t_envp *p;

	tmp = main_data.list_envp;
	if (tmp == NULL)
		return (NULL);
	head = malloc(sizeof(t_envp));
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
	tmp = NULL;
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
		write(fd, "declare -x ", ft_strlen("declare - x"));
		write(fd, tmp->name, ft_strlen(tmp->name));

		if(ft_strchr(tmp->name, '='))
		{
			write(fd, "\"", 1);
			write(fd, tmp->value, ft_strlen(tmp->value));
			write(fd, "\"\n", 2);
		}
		else
			write(fd, "\n", 1);
		tmp = tmp->next;
	}
	while (copy)
		rem_envp_VAR(&copy, copy->name);
}

int	valid_export(char *arg, char *out)
{
	if (ft_overlap(arg, "<>;-+?~)(\\|") || ft_isdigit(arg[0]))
	{
		write(2, "export : `", 11);
		write(2, out, ft_strlen(out));
		write(2, "' : not a valid identifier", 27);
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}

void	export(t_cmd *cmd, int fd)
{
	char	*check;
	t_envp	*tmp;
	char	*name_var;
	char	*rename;
	int		i;

	if (!cmd->arg[1])
	{
		print_export(fd);
		return ;
	}
	i = 1;
	while (cmd->arg[i])
	{
		printf("%s\n", cmd->arg[i]);
		i++;
	}
	
	i = 1;
	while(cmd->arg[i])
	{
	check = ft_strchr(cmd->arg[i], '=');
	if(check)
	{
		name_var = ft_substr(cmd->arg[i], 0, check - cmd->arg[i]);
		if (valid_export(name_var, cmd->arg[i]))
			return ;
		tmp = find_var_envp(main_data.list_envp, name_var);
		free(name_var);
		if (!tmp)
		{
			tmp = new_envp(cmd->arg[i], NULL);
			lastadd_envp(main_data.list_envp, tmp);
		}
		else
		{
			free(tmp->value);
			if (!ft_strchr(tmp->name, '='))
			{
				rename = tmp->name;
				tmp->name = ft_strjoin(rename, "=");
				free(rename);
			}
			tmp->value = ft_substr(cmd->arg[i], (check - cmd->arg[i]) + 1, ft_strlen(check));
		}
	}
	else
	{
		if (valid_export(cmd->arg[i], cmd->arg[i]))
			return ;
		tmp = find_var_envp(main_data.list_envp, cmd->arg[i]);
		if (!tmp)
		{
			tmp = new_envp(cmd->arg[i], NULL);
			lastadd_envp(main_data.list_envp, tmp);
		}
	}
	i++;
	}
	
}