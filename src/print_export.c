#include "../includes/minishell.h"
static void	copying_process(t_envp *tmp, t_envp *p)
{
	while (tmp)
	{
		if (!ft_strncmp("_=", tmp->name, 3))
		{
			tmp = tmp->next;
			continue ;
		}
		p->next = malloc_x(sizeof(t_envp));
		p = p->next;
		p->name = ft_strdup(tmp->name);
		p->value = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	p->next = NULL;
}

static t_envp	*make_copy_envp(void)
{
	t_envp	*tmp;
	t_envp	*head;
	t_envp	*p;

	tmp = g_main_data.list_envp;
	if (tmp == NULL)
		return (NULL);
	head = malloc_x(sizeof(t_envp));
	head->name = ft_strdup(tmp->name);
	head->value = ft_strdup(tmp->value);
	p = head;
	tmp = tmp->next;
	copying_process(tmp, p);
	return (head);
}

static void	changing_places(t_envp *tmp, t_envp *tmp1)
{
	char	*tmp_name;
	char	*tmp_value;

	tmp_name = tmp->name;
	tmp_value = tmp->value;
	tmp->name = tmp1->name;
	tmp->value = tmp1->value;
	tmp1->value = tmp_value;
	tmp1->name = tmp_name;
}

static t_envp	*sort_envp(t_envp *head)
{
	t_envp	*tmp;
	t_envp	*tmp1;

	if (!head)
		return (NULL);
	tmp = head;
	while (tmp)
	{
		tmp1 = tmp->next;
		while (tmp1)
		{
			if (ft_strncmp(tmp->name, tmp1->name, ft_strlen(tmp->name) + 1) > 0)
				changing_places(tmp, tmp1);
			tmp1 = tmp1->next;
		}
		tmp = tmp->next;
	}
	tmp = NULL;
	return (head);
}

void	print_export(int fd)
{
	t_envp	*copy;
	t_envp	*tmp;

	copy = make_copy_envp();
	copy = sort_envp(copy);
	tmp = copy;
	while (tmp)
	{
		write(fd, "declare -x ", ft_strlen("declare - x"));
		write(fd, tmp->name, ft_strlen(tmp->name));
		if (ft_strchr(tmp->name, '='))
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
