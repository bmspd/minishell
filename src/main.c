
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
	return (ft_substr(str, 0, len + 1));
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
int main(int argc, char **argv, char **env) {

	init_title();
	main_data.hist_flag = 0;
	main_data.cursor_place = 0;
	main_data.env0 = env;
	main_data.null_flag = 0;
	char str[2000];
	int l;
	int n;
	main_data.history_id = -1;

	struct termios term;
	name = getenv("TERM");
//	printf("%s\n", name);
//	if (argc == 2 && strcmp(argv[1], "full_screen") == 0)
//		test_clean_screen();
	tcgetattr(0, &term); // for making changes with echo - set different params for term
	term.c_lflag &= ~(ECHO); // making bits for echo to zero, to make text invisible
	term.c_lflag &= ~(ICANON); // not canon mode, when typing does not stop by ENTER(by any pushed button)
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
		main_data.buf_hist_cpy = ft_strdup("");
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
				if (strcmp(str,"\n"))
				{
					main_data.buf_hist = ft_strjoin(main_data.buf_hist, str);
					main_data.history_id = -1;
					main_data.cursor_place += ft_strlen(str);
				}
			}
			if (!strcmp(str, "\n") || !strcmp(str, "\4"))
			{
				break ;
			}
		}

		if (strcmp(main_data.buf_hist, ""))
		{
			main_data.counter = 0;
			main_data.flag1 = 0;
			ft_lstadd_back(&main_data.commands, ft_lstnew(NULL));
			init_commands();
			parser(delete_spaces_behind(main_data.buf_hist), env);
//			printf("----------------------------------------\n");
//			t_list *tmp = main_data.commands;
//			while (tmp)
//			{
//				int r = 0;
//				while (tmp->commands[r])
//				{
//					printf("[%d]:|%s|\n", tmp->id, tmp->commands[r]);
//					r++;
//				}
//				printf("---->[%s]<----\n", tmp->flag);
//				tmp = tmp->next;
//			}
			if (extra_parser())
			{
				//функция запуска комманд <-----где-то здесь должна быть
			}
//			main_data.commands->commands = NULL;
//			main_data.commands->flag = NULL;
//			main_data.commands->id = 0;
			main_data.commands = NULL;
			main_data.null_flag = 0;
			ft_lstadd_front(&main_data.history, ft_lstnew(main_data.buf_hist));
			numerate_history(main_data.history);
			main_data.history_id = -1;
			main_data.cursor_place = 0;
		}

	}
	write(1, "\nExiting...\n", ft_strlen("\nExiting...\n"));
}
