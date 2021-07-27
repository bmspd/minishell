
#include "../includes/minishell.h"
char info[2048];
char *name;
char buf[100];
char *buffer;
t_struct main_data;

void	print_cmds(void)
{
	printf("----------------------------------------\n");
	int i;

	i = 0;
	t_list *tmp = main_data.commands;
	while (tmp)
	{
		int r = 0;
		while (tmp->commands[r])
		{
			printf("[number_list %d][%d]:|%s| :[length %lu]\n", i, tmp->id, tmp->commands[r], ft_strlen(tmp->commands[r]));
			r++;
		}
		printf("---->[number_list %d][%s]<----\n", i, tmp->flag);
		tmp = tmp->next;
					i++;
	}
}


void	free_arr(char **arr, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		i++;
	}
	free(arr);
}

/* this for exec cmd - ------- - --- - - - - ------------------ ------------ --- -- ---------- -- - --- -- ------- -- - - -- --*/

int	look_in_direction(char *path, char *find_file)
{
	DIR *direction;
	struct dirent *file;

	file = NULL;
	direction = opendir(path);

	if (direction)
		file = readdir(direction);
	while (file)
	{
		if (!ft_strncmp(find_file, file->d_name, ft_strlen(find_file) + 1))
		{
			closedir(direction);
			return (1);
		}
		file = readdir(direction);
	}
	if (direction)
		closedir(direction);
	return (0);
}

char *find_path_cmd(char *value, char *name_prog, char *home)
{
	char **paths;
	char *tmp;
	char *out;
	int i;
	char *tmp_name;

	tmp_name = ft_strdup(name_prog);
	i = 0;
	if (!value)
		return (NULL);
	paths = ft_split(value, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		if(!ft_strncmp(paths[i], "~", 1))
		{
			if (!home)
				break;
			tmp = paths[i];
			paths[i] = ft_strjoin(home, ft_strchr(tmp, '/'));
			free(tmp);
		}
		i++;
	}
	i = 0;
	while (paths[i])
	{
		if (look_in_direction(paths[i], tolower_str(tmp_name)))
		{
			tmp = ft_strjoin("/", tmp_name);
			out = ft_strjoin(paths[i], tmp);
			free(tmp);
			free(tmp_name);
			free_arr(paths, count_arr(paths));
			return (out);
		}
		i++;
	}
	free(tmp_name);
	free_arr(paths, count_arr(paths));
	return (NULL);
}

int		count_list(t_envp *list)
{
	int i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

char *convert_in_str(char *s1, char *s2)
{
	char *out;

	out = ft_strjoin(s1, s2);
	return (out);
}

char **convert_list_in_arr(t_envp *list_envp)
{
	int count;
	char **envp;
	int i;

	count = count_list(list_envp);
	envp = malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		envp[i] = convert_in_str(list_envp->name, list_envp->value);
		i++;
		list_envp = list_envp->next;
	}
	envp[i] = NULL;
	return (envp);
}

/* end exec cmd - -- -- -- -- -- -- --- -- -- --- -- -- -- -- -- -- -- -- -- -- --- --- --- --- --- --- --- -- -- -- -- - */


int main(int argc, char **argv, char **env)
{
	init_title();
	init_variables();

	main_data.list_envp = create_list_envp(env);
	external_history();
	set_terminal(1);
	if (main_data.ws.ws_col >= 106)
		print_big_greeting();
	else if (main_data.ws.ws_col < 106)
		print_small_greeting();

	while (10)
	{
		print_title();
		main_data.buf_hist = ft_strdup("");
		typing_cycle();
		if(!ft_strncmp("exit", main_data.buf_hist, 6) || !ft_strncmp("\4", main_data.buf_hist, 2))
			break;
		if (ft_strncmp(main_data.buf_hist, "", 2))
			main_engine();
		else
			free(main_data.buf_hist);

	}
	set_terminal(0);
	write(1, "💔💔💔 \x1b[36msee ya later \x1b[31m↻\x1b[0m\n",
		  ft_strlen("💔💔💔 \x1b[36msee ya later \x1b[31m↻\x1b[0m\n"));
	return (0);
}
