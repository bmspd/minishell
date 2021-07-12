
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
	int tmp_flag = 0;
	t_list	*tmp = main_data.commands;
	//printf("[%d]\n", ft_lstsize(main_data.commands));
	if (ft_lstsize(main_data.commands) >= 2)
	{
		if (ft_strncmp(tmp->flag, "|", 2) && ft_strncmp(tmp->flag, ";", 2))
			tmp = tmp->next;
	}
	while (tmp)
	{
		if (tmp->id == ft_lstsize(main_data.commands) - 1 && tmp_flag)
			return (1);
		if (tmp->commands[0] == NULL)
		{
			printf("PARSER ERROR!\n");
			return (0);
		}
		if (tmp->flag)
		{
			if (!ft_strncmp(tmp->flag, ";", 2))
				tmp_flag = 1;
			else
				tmp_flag = 0;
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
	t_list *tmp = main_data.commands;
	while (tmp)
	{
		int r = 0;
		while (tmp->commands[r])
		{
			printf("[%d]:|%s| :[length %lu]\n", tmp->id, tmp->commands[r], ft_strlen(tmp->commands[r]));
			r++;
		}
		printf("---->[%s]<----\n", tmp->flag);
		tmp = tmp->next;
	}
}


void	free_arr(char **arr, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		if (arr[i])
			free(arr[i]);
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

char *find_path_cmd(char *value, char *name_prog, char *pwd)
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

			paths[i] = ft_strjoin(pwd, ft_strchr(tmp, '/'));
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

void	exec_fork(char	**prog, ENV *PATH, char **envp, ENV *PWD)
{
	pid_t pid;
	char	*path;

	if (PATH)
		path = find_path_cmd(PATH->value, prog[0], PWD->value);
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

int		builtin(t_list *cmd, ENV **list_envp)
{
	int i;

	i = 0;
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

	// print_cmds();

	while (cmd)
	{
		if(cmd->commands[0])
		{
			if (builtin(cmd, list_envp))
			;
			else
				exec_fork(cmd->commands, find_VAR_ENV(*list_envp, "PATH"), convert_list_in_arr(*list_envp),
						  find_VAR_ENV(*list_envp,"HOME"));
		}
		cmd = cmd->next;
	}	
}

/* end exec cmd - -- -- -- -- -- -- --- -- -- --- -- -- -- -- -- -- -- -- -- -- --- --- --- --- --- --- --- -- -- -- -- - */


void handler1 (int status)
{
	if (status == SIGINT)
		printf("\n");
	if (status == SIGQUIT)
		printf("Quit: 3\n");
}
int main(int argc, char **argv, char **env) {

	init_title();
	main_data.hist_flag = 0;
	main_data.cursor_place = 0;
	main_data.env0 = env;
	main_data.null_flag = 0;
	main_data.key_amount = 0;
	main_data.buf_hist = NULL;
	char str[2000];
	int l;
	int n;
	main_data.history_id = -1;
	ENV	*list_envp;

	list_envp = create_list_envp(env);
	struct termios term;
	struct termios saved;
	name = "xterm-256color";
	tcgetattr(0, &term); // for making changes with echo - set different params for term
	term.c_lflag &= ~(ECHO); // making bits for echo to zero, to make text invisible
	term.c_lflag &= ~(ICANON); // not canon mode, when typing does not stop by ENTER(by any pushed button)
	//printf("[%d]:[%d]\n", term.c_cc[VMIN], term.c_cc[VTIME]);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0; //whait of read to close
	tcsetattr(0, TCSANOW, &term); // get start, default params to term
	tgetent(0, name); //switching termcap capabilities
//	printf("%s\n", argv[0]);
	signal(SIGQUIT, handler);
	signal(SIGINT, handler);
	signal(SIGWINCH, handler);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &main_data.ws);
	while (strcmp(str, "\4"))
	{
		print_title();
		main_data.buf_hist = ft_strdup("");
		while(10)
		{
			ioctl(0, FIONREAD, &n);
			l = read(0, str, 2000);
			str[l] = 0;
			if (key_control(str))
				;
			else
			{
				write(1, str, l);
				main_data.key_amount++;
				if (strcmp(str,"\n"))
				{
					char *tmp0 = ft_substr(main_data.buf_hist, 0, main_data.cursor_place);
					char *tmp1 = ft_strjoin(tmp0, str);
					char *tmp2 = ft_substr(main_data.buf_hist, main_data.cursor_place,
										   ft_strlen(main_data.buf_hist) - main_data.cursor_place);
					//main_data.buf_hist = ft_strjoin(tmp, str);
					free(main_data.buf_hist);
					main_data.buf_hist = ft_strjoin(tmp1, tmp2);
					main_data.cursor_place += ft_strlen(str);
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
					//main_data.buf_hist = ft_strjoin(main_data.buf_hist, str);
					main_data.history_id = -1;
					free(tmp0);
					free(tmp2);
					free(tmp1);
				}
			}
			if (!strcmp(str, "\n") || !strcmp(str, "\4"))
			{
				break ;
			}
		}
		if(!ft_strncmp("exit", main_data.buf_hist, 6))
			break;
		if (strcmp(main_data.buf_hist, ""))
		{
			main_data.counter = 0;
			main_data.flag1 = 0;
			ft_lstadd_back(&main_data.commands, ft_lstnew(NULL));
			init_commands();
			parser(delete_spaces_behind(main_data.buf_hist), env);
			//print_cmds();
			if (extra_parser() && strcmp(str, "\4"))
			{
				term.c_lflag |= (ECHO); // making bits for echo to zero, to make text invisible
				term.c_lflag |= (ICANON);
				tcsetattr(0, TCSANOW, &term);
				signal(SIGINT, handler1);
				signal(SIGQUIT, handler1);
				read_cmd(main_data.commands, &list_envp);	//функция запуска комманд <-----где-то здесь должна быть

				term.c_lflag &= ~(ECHO); // making bits for echo to 1, to make text invisible
				term.c_lflag &= ~(ICANON);
				tcsetattr(0, TCSANOW, &term);
				signal(SIGINT, handler);
				signal(SIGQUIT, handler);
			}
			//cleaning
			while (main_data.commands)
			{
				t_list *zozo = NULL;
				int k = 0;
				while (main_data.commands->commands[k])
				{
					free(main_data.commands->commands[k]);
					k++;
				}
				free(main_data.commands->commands[k]);
				free(main_data.commands->commands);
				free(main_data.commands->flag);

				if (main_data.commands->next)
					zozo = main_data.commands->next;
				free(main_data.commands);
				main_data.commands = zozo;
			}

			main_data.commands = NULL;
			//end cleaning
			main_data.null_flag = 0;
			ft_lstadd_front(&main_data.history, ft_lstnew_history(main_data.buf_hist, main_data.key_amount - 1));
			main_data.key_amount = 0;
			numerate_history(main_data.history);
			main_data.history_id = -1;
			main_data.cursor_place = 0;


		}
		else
			free(main_data.buf_hist);

	}
	write(1, "\nExiting...\n", ft_strlen("\nExiting...\n"));
}
