
#include "../includes/minishell.h"
char info[2048];
char *name;
char buf[100];
char *buffer;
t_struct main_data;

//Получение ширины и высоты терминала на текущий момент
void	test_tgetnum(void)
{
	int col;
	int line;

	col = tgetnum("co");
	line = tgetnum("li");
	printf("Текущие параметры терминала: Ширина = %d, Высота = %d\n", col, line);
}

void 	test_clean_screen(void)
{
	char *clean_screen;

	buffer = buf;
	clean_screen = tgetstr("cl", &buffer);
	tputs(clean_screen, 1, ft_putint);

	buffer = buf;
	bzero(buffer, 100);

}

char	*delete_spaces_behind(char *str)
{
	int	len;

	len = (int)ft_strlen(str) - 1;
	while (str[len] == ' ')
	{
		len--;
	}
	// free(str);  Определенно не тут :)
	char *tmp = ft_substr(str, 0, len + 1);
	return (tmp);
}

int extra_parser(void)
{
	int last_flag_pipe = 0;
	int tmp_flag = 0;
	t_list	*tmp = main_data.commands;
//	if (ft_lstsize(main_data.commands) >= 2)
//	{
//		if (ft_strncmp(tmp->flag, "|", 2) && ft_strncmp(tmp->flag, ";", 2))
//			tmp = tmp->next;
//	}
	if (ft_lstsize(tmp) == 1 && !tmp->commands[0])
		return (1);
	while (tmp)
	{

		if (tmp->id == ft_lstsize(main_data.commands) - 1 && tmp_flag)
			return (1);
		if (tmp->commands[0] == NULL)
		{
			if (last_flag_pipe && (!ft_strncmp("<", tmp->flag, 2)
				|| !ft_strncmp("<<", tmp->flag, 3) || !ft_strncmp(">>", tmp->flag, 3)
				|| !ft_strncmp(">", tmp->flag, 2)))
				;
			else if (!ft_strncmp("<", tmp->flag,  2)
				|| !ft_strncmp("<<", tmp->flag,  3) || !ft_strncmp(">>", tmp->flag,  3)
				|| !ft_strncmp(">", tmp->flag,  2))
				;
			else
			{
				printf("PARSER ERROR!\n");
				return (0);
			}
		}
		if (tmp->flag)
		{
			if (!ft_strncmp(tmp->flag, ";", 2))
				tmp_flag = 1;
			else
				tmp_flag = 0;
		}
		if (tmp->flag)
		{
			if (!ft_strncmp(tmp->flag, "|", 2))
				last_flag_pipe = 1;
			else
				last_flag_pipe = 0;
		}
		tmp = tmp->next;
	}
	return (1);

}

t_list	*ft_lstnew_history(void *content, int amount)
{
	t_list	*new;

	new = (struct s_list *)malloc(sizeof(t_list));
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


void set_terminal(int type)
{
	main_data.term_name = "xterm-256color";
	tcgetattr(0, &main_data.term);
	if (type == 1)
	{
		signal(SIGQUIT, handler);
		signal(SIGINT, handler);
		main_data.term.c_lflag &= ~(ECHO);
		main_data.term.c_lflag &= ~(ICANON);
	}
	else
	{
		signal(SIGQUIT, handler1);
		signal(SIGINT, handler1);
		main_data.term.c_lflag |= (ECHO);
		main_data.term.c_lflag |= (ICANON);
	}
	main_data.term.c_cc[VMIN] = 1;
	main_data.term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &main_data.term);
	tgetent(0, main_data.term_name);
	signal(SIGWINCH, handler);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &main_data.ws);
}

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

int open_history(int flag)
{
	char *filename;
	int fd;
	char *full;
	char *path = getenv("HOME");
	if (path)
	{
		filename = "/.hist";
		full = ft_strjoin(path, filename);
		fd = open(full, O_CREAT| O_RDWR | flag , S_IRWXU);
		free(full);
	}
	else
	{
		filename = ".hist";
		fd = open(filename, O_CREAT| O_RDWR | flag , S_IRWXU);
	}
	return (fd);
}
void external_history()
{
	char *line;
	int fd = open_history(0);
//	printf("%d\n", fd);
	int i;
	i = 1;
	while (i)
	{
		i = get_next_line(fd, 128, &line);
//		printf("|%s|\n", line);
		if (!ft_strlen(line))
		{
			free(line);
			continue ;
		}
		ft_lstadd_back(&main_data.history, ft_lstnew_history(line, ft_strlen(line)));
		numerate_history(main_data.history);
	}
	t_list *tempo = main_data.history;
	while (tempo)
	{
//		printf("|%s|[%d]\n", (char *)tempo->content, tempo->key_amount);
		tempo = tempo->next;
	}
	close(fd);
}

void fill_external_history(int fd)
{
	t_list *tmp;

	tmp = main_data.history;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, "\4", 2))
		{
//			printf("%lu\n", ft_strlen((char *)tmp->content));
//			printf("|%s|\n", (char *)tmp->content);
			ft_putstr_fd(tmp->content, fd);
			ft_putchar_fd('\n', fd);
		}
		tmp = tmp->next;
	}
	close(fd);
}
void    symbol_not_enter(char *str)
{
	char    *tmp0;
	char    *tmp1;
	char    *tmp2;

	safe_free(main_data.part);
	main_data.part = NULL;
	main_data.current_tab = 0;
	main_data.buf_flag = 0;
	tmp0 = ft_substr(main_data.buf_hist, 0, main_data.cursor_place);
	tmp1 = ft_strjoin(tmp0, str);
	tmp2 = ft_substr(main_data.buf_hist, main_data.cursor_place,
						   ft_strlen(main_data.buf_hist) - main_data.cursor_place);
	free(main_data.buf_hist);
	main_data.buf_hist = ft_strjoin(tmp1, tmp2);
	//if (ft_strncmp("\4", str, 2))
	main_data.cursor_place += (int)ft_strlen(str);
	write(1, tmp2, ft_strlen(tmp2));
	if (main_data.cursor_place != ft_strlen(main_data.buf_hist))
	{
		int z = 0;
		while (z < ft_strlen(tmp2))
		{
			tputs(cursor_left, 1, ft_putint);
			z++;
		}
	}
	main_data.history_id = -1;
	free(tmp0);
	free(tmp2);
	free(tmp1);
}

void    typing_cycle()
{
	char str[2000];
	int l;

	while(10)
	{
		l = read(0, str, 2000);
		str[l] = 0;
		if (key_control(str))
			;
		else
		{
			if (ft_strncmp("\4", str, 2))
			{
				write(1, str, l);
				main_data.key_amount++;
				if (ft_strncmp("\n", str, 2))
					symbol_not_enter(str);
			}

		}
		if (!ft_strncmp("\4", str, 2) && (!ft_strncmp("\4", str, 2) && !ft_strncmp("", main_data.buf_hist, 2)))
		{
			safe_free(main_data.buf_hist);
			main_data.buf_hist = ft_strdup("\4");
			write(1, "exit\n", 6);
			break ;
		}
		if (!ft_strncmp("\n",str, 2))
		{
			break ;
		}
	}
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
	char str[2000];

	int l;
	int n;
	ENV	*list_envp;


	list_envp = create_list_envp(env);
	main_data.list_envp = create_list_envp(env);
	external_history();
	set_terminal(1);

	while (ft_strncmp("\4", str, 2))
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
				read_cmd(main_data.commands, &list_envp);	//функция запуска комманд <-----где-то здесь должна быть
				set_terminal(1);
				int len = (int)count_arr(elements);
				free_arr(elements, len);
				free_arr(help_elements, len);
			}
			cleaning_foo();
			int fd = open_history(O_TRUNC);
			ft_lstadd_front(&main_data.history, ft_lstnew_history(main_data.buf_hist, main_data.key_amount - 1));
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
