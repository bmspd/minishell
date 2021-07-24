#include "../includes/minishell.h"

void	handler(int status)
{
	if (status == SIGINT)
	{
		moveback_cursor();
		ft_putstr(main_data.buf_hist);
		write(STDIN_FILENO, "\n", 1);
		print_title();
		free(main_data.buf_hist);
		main_data.buf_hist = ft_strdup("");
		main_data.history_id = -1;
		main_data.key_amount = 0;
		main_data.current_tab = 0;
		free(main_data.old_buf_hist);
		main_data.old_buf_hist = ft_strdup("");
		main_data.part = NULL;
	}
	if (status == SIGWINCH)
		ioctl(STDIN_FILENO, TIOCGWINSZ, &main_data.ws);
	if (status == SIGQUIT)
		write(1, "\a", 1);
}

void	handler1(int status)
{
	if (status == SIGINT)
		printf("\n");
	if (status == SIGQUIT)
		printf("Quit: 3\n");
}

void	set_terminal(int type)
{
	main_data.term_name = "xterm-256color";
	tcgetattr(0, &main_data.term);
	if (type == 1)
	{
		signal(SIGSTOP, handler);
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
