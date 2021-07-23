
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

void	print_arg(char **arg)
{
	int i;

	i = 0;
	printf("------------------\n");
	while (arg[i])
	{
		printf("%s\n",arg[i]);
		i++;
	}
}

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

	i = 0;
	paths = ft_split(value, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		if(!ft_strncmp(paths[i], "~", 1))
		{
			tmp = paths[i];
			paths[i] = ft_strjoin(home, ft_strchr(tmp, '/'));
			free(tmp);
		}
		i++;
	}
	i = 0;
	while (paths[i])
	{
		if (look_in_direction(paths[i], name_prog))
		{
			tmp = ft_strjoin("/", name_prog);
			out = ft_strjoin(paths[i], tmp);
			free(tmp);
			free_arr(paths, count_arr(paths));
			return (out);
		}
		i++;
	}
	free_arr(paths, count_arr(paths));
	return (NULL);
}

void	exec_fork(char	**prog, ENV *PATH, char **envp, ENV *HOME)
{
	pid_t pid;
	char	*path;

	if (PATH)
		path = find_path_cmd(PATH->value, prog[0], HOME->value);
	else
		path = NULL;
	if (!path)
		path = prog[0];
	pid = fork();
	wait(0);
	if(!pid)
	{
		execve(path, prog, envp);
		perror(prog[0]);
		exit (EXIT_FAILURE);
	}
	if (path && ft_strncmp(prog[0], path, ft_strlen(path)))
		free(path);
	free_arr(envp, count_arr(envp));
}

int		count_list(ENV *list)
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
	char *tmp;
	char *out;

	tmp = ft_strjoin(s1, "=");
	out = ft_strjoin(tmp, s2);
	free(tmp);
	return (out);
}

char **convert_list_in_arr(ENV *list_envp)
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

int	creat_file(char *name_file)
{
	int fd;

	fd = open(name_file, O_RDWR | O_CREAT | O_TRUNC, 0777);
	return (fd);
}

int		builtin(t_list *cmd, ENV **list_envp)
{
	int i;

	i = 0;
	if (!cmd->commands[0])
		return (i);
	if (!ft_strncmp(cmd->commands[0], "env", 4))
	{
		env(*list_envp);
		i = 1;
	}
	if (!ft_strncmp(cmd->commands[0], "cd", 3))
	{
		go_to_direction(cmd->commands[1], *list_envp);
		i = 1;
	}
	if ((!ft_strncmp(cmd->commands[0], "unset", 6)))
	{
		rem_envp_VAR(list_envp, cmd->commands[1]);
		i = 1;
	}
	if ((!ft_strncmp(cmd->commands[0], "pwd", 6)))
	{
		print_pwd();
		i = 1;
	}
	return (i);
}


void	read_cmd(t_list *cmd, ENV **list_envp)
{

	int i;
	// print_cmds();
	i = 0;
	while (cmd)
	{
		// if(cmd->commands[0])
		// {
			if (builtin(cmd, list_envp))
			;
			// else
			// {
			// 	// read_flag(cmd);
			// }
			// i++;
			// if (!ft_strncmp("<<", cmd->flag, 3))
			// 	heredoc(cmd->next->commands[0]);
			else
				exec_fork(cmd->commands, find_VAR_ENV(*list_envp, "PATH"), convert_list_in_arr(*list_envp),
						  find_VAR_ENV(*list_envp,"HOME"));
		// }
		cmd = cmd->next;
	}	
}

/* end exec cmd - -- -- -- -- -- -- --- -- -- --- -- -- -- -- -- -- -- -- -- -- --- --- --- --- --- --- --- -- -- -- -- - */

void	cleaning_foo(void)
{
	t_list	*tmp;
	int		k;

	while (main_data.commands)
	{
		tmp = NULL;
		k = 0;
		while (main_data.commands->commands[k])
			free(main_data.commands->commands[k++]);
		free(main_data.commands->commands[k]);
		free(main_data.commands->commands);
		free(main_data.commands->flag);

		if (main_data.commands->next)
			tmp = main_data.commands->next;
		free(main_data.commands);
		main_data.commands = tmp;
	}
	main_data.commands = NULL;
	main_data.null_flag = 0;
	main_data.key_amount = 0;
	main_data.history_id = -1;
	main_data.cursor_place = 0;
}

int main(int argc, char **argv, char **env) {


	init_title();
	main_data.cursor_place = 0;
	main_data.null_flag = 0;
	main_data.key_amount = 0;
	main_data.buf_hist = NULL;
	main_data.history = NULL;
	main_data.current_tab = 0;
	main_data.part = NULL;
	main_data.buf_flag = 0;
	main_data.history_id = -1;

	ENV	*list_envp;


	list_envp = create_list_envp(env);
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
		{
			main_data.counter = 0;
			main_data.flag1 = 0;
			main_data.current_tab = 0;
			main_data.part = NULL;
			ft_lstadd_back(&main_data.commands, ft_lstnew(NULL));
			init_commands();
			parser(delete_spaces_behind(main_data.buf_hist));
			if (extra_parser() && ft_strncmp(main_data.buf_hist, "\4", 2))
			{
				char **elements = list_to_char();
				char **help_elements = list_to_help_char();
				int i = 0;
				while(elements[i])
				 {
					 printf("|%s|[%s]\n", elements[i], help_elements[i]);
					 i++;
				 }
				set_terminal(0);
				//read_cmd(main_data.commands, &list_envp);	//функция запуска комманд <-----где-то здесь должна быть
				set_terminal(1);
				int len = (int)count_arr(elements);
				free_arr(elements, len);
				free_arr(help_elements, len);
			}
			cleaning_foo();
			int fd = open_history(O_TRUNC);
			ft_lstadd_front(&main_data.history, ft_lstnew_history(main_data.buf_hist, (int)ft_strlen(main_data.buf_hist)));
			numerate_history(main_data.history);
			fill_external_history(fd);

		}
		else
			free(main_data.buf_hist);

	}
	set_terminal(0);

	write(1, "💔💔💔 \x1b[36msee ya later \x1b[31m↻\x1b[0m\n",
		  ft_strlen("💔💔💔 \x1b[36msee ya later \x1b[31m↻\x1b[0m\n"));
}
