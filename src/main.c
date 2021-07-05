
#include "../includes/minishell.h"
char info[2048];
char *name;
char buf[100];
char *buffer;
t_struct main_data;
int	ft_putint(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}
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


void handler (int status)
{
	if (status == SIGINT)
	{
		if (ft_strlen(main_data.buf_hist))
		{
			int i = (main_data.title_length + (int)ft_strlen(main_data.buf_hist)) / main_data.ws.ws_col;
			while (i)
			{
				tputs(tgetstr("cr", 0), 1, ft_putint);
				tputs(tigetstr("ed"), 1, ft_putint);
				tputs(tgetstr("up", 0), 1, ft_putint);
				i--;
			}

		}
		tputs(tgetstr("cr", 0), 1, ft_putint);
		tputs(tigetstr("ed"), 1, ft_putint);
		print_title();
		write(STDIN_FILENO, "\n", 1);
		print_title();
		main_data.buf_hist = ft_strdup("");
	}
	if (status == SIGWINCH)
	{
		ioctl(STDIN_FILENO, TIOCGWINSZ, &main_data.ws);
	}
}

void numerate_history(t_list *history)
{
	t_list *tmp;
	tmp = history;
	int i = 0;
	while (tmp)
	{
		tmp->id = i;
		tmp = tmp->next;
		i++;
	}
}

void take_history(void)
{
	t_list *tmp;
	tmp = main_data.history;
	while (tmp)
	{
		if (tmp->id == main_data.history_id)
		{
			main_data.buf_hist = ft_strdup(main_data.history->content);
			ft_putstr(tmp->content);
		}
		tmp = tmp->next;
	}
}

int main(int argc, char **argv) {

	init_title();
	main_data.hist_flag = 0;
	char str[2000];
	int l;
	int n;
	main_data.history_id = -1;
	struct termios term;
	name = getenv("TERM");
	printf("%s\n", name);
	if (argc == 2 && strcmp(argv[1], "full_screen") == 0)
		test_clean_screen();
	tcgetattr(0, &term); // for making changes with echo - set different params for term
	term.c_lflag &= ~(ECHO); // making bits for echo to zero, to make text invisible
	term.c_lflag &= ~(ICANON); // not canon mode, when typing does not stop by ENTER(by any pushed button)
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0; //whait of read to close
	tcsetattr(0, TCSANOW, &term); // get start, default params to term
	printf("%d\n", tgetent(0, name)); //switching termcap capabilities
	printf("%s\n", argv[0]);
	signal(SIGINT, handler);
	signal(SIGWINCH, handler);
//	main_data.abs_col = tgetnum("co");
//	main_data.abs_line = tgetnum("li");
	ioctl(STDIN_FILENO, TIOCGWINSZ, &main_data.ws);
	while (strcmp(str, "\4"))
	{
		print_title();
		tputs(save_cursor, 1, ft_putint);
		main_data.buf_hist = ft_strdup("");
		while(1)
		{
			ioctl(0, FIONREAD, &n);
			l = read(0, str, 5);
			str[l] = 0;
			if (!strcmp(str, "\e[A")) // UP
			{


				if (ft_strlen(main_data.buf_hist))
				{
					int i = (main_data.title_length + (int)ft_strlen(main_data.buf_hist)) / main_data.ws.ws_col;
					while (i)
					{
						tputs(tgetstr("cr", 0), 1, ft_putint);
						tputs(tigetstr("ed"), 1, ft_putint);
						tputs(tgetstr("up", 0), 1, ft_putint);
						i--;
					}

				}
				tputs(tgetstr("cr", 0), 1, ft_putint);
				tputs(tigetstr("ed"), 1, ft_putint);
				print_title();
				main_data.buf_hist = ft_strdup("");
				if (main_data.history_id < ft_lstsize(main_data.history) || ft_lstsize(main_data.history))
				{
					main_data.history_id += 1;
					take_history();

				}
				else
					write(1, "\a", 1);
			}
			else if (!strcmp(str, "\e[B")) //DOWN
			{
				if (ft_strlen(main_data.buf_hist))
				{
					int i = (main_data.title_length + (int)ft_strlen(main_data.buf_hist)) / main_data.ws.ws_col;
					while (i)
					{
						tputs(tgetstr("cr", 0), 1, ft_putint);
						tputs(tigetstr("ed"), 1, ft_putint);
						tputs(tgetstr("up", 0), 1, ft_putint);
						i--;
					}

				}
				tputs(tgetstr("cr", 0), 1, ft_putint);
				tputs(tigetstr("ed"), 1, ft_putint);
				print_title();
				main_data.buf_hist = ft_strdup("");
				if (main_data.history_id > -1)
				{
					main_data.history_id -= 1;
					take_history();
				}
				else
					write(1, "\a", 1);
			}
			else if (!strcmp(str, "\e[D")) //LEFT
			{
				tputs(tgetstr("rc", 0), 1, ft_putint);
				if (ft_strlen(main_data.buf_hist))
				{
					int i = (main_data.title_length + (int)ft_strlen(main_data.buf_hist)) / main_data.ws.ws_col;
					while (i)
					{
						tputs(tgetstr("up", 0), 1, ft_putint);
						i--;
					}


				}
			}
			else if (!strcmp(str, "\e[C")) // RIGHT
			{
				;//tputs(tgetstr("cl", 0), 1, ft_putint);
			}
			else if (!strcmp(str, "\177")) {
				if (!ft_strlen(main_data.buf_hist))
				{
					write(1, "\a", 1);
					continue ;
				}
				tputs(cursor_left, 1, ft_putint);
				tputs(tigetstr("ed"), 1, ft_putint);
				ft_strlcpy(main_data.buf_hist, main_data.buf_hist, ft_strlen(main_data.buf_hist));
			}
			else
			{
				write(1, str, l);
				if (strcmp(str,"\n"))
				{
					main_data.buf_hist = ft_strjoin(main_data.buf_hist, str);
					main_data.history_id = -1;
				}
			}
			if (!strcmp(str, "\n") || !strcmp(str, "\4"))
				break ;
		}

		if (strcmp(main_data.buf_hist, ""))
		{
			ft_lstadd_front(&main_data.history, ft_lstnew(main_data.buf_hist));
			numerate_history(main_data.history);
			main_data.history_id = -1;
		}
//		int i = 0;
//		t_list *tmp = main_data.history;
//		while (tmp)
//		{
//			printf("[%d]:%s\n",tmp->id, (char *)tmp->content);
//			//printf("%s\n", (char *)tmp->content);
//			tmp = tmp->next;
//		}
	}
	write(1, "\n", 1);
}
