
#ifndef MINISHELL_H
#define MINISHELL_H

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define CLR_RESET   "\x1b[0m"

# define ESC_DOWN		"\e[B"
# define ESC_UP			"\e[A"
# define ESC_LEFT		"\e[D"
# define ESC_RIGHT		"\e[C"
# define ESC_BACKSPACE	"\177"
#include "../libft/libft.h"

#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>


typedef struct s_struct{
	t_list *history;
	int	history_id;
	int hist_flag;
	char *buf_hist;
	char *buf_hist_cpy;
	char *title;
	int	title_length;
	int abs_col;
	int	abs_line;
	int cursor_place;
	struct winsize ws;
	t_list *commands;
	int flag1;
	int counter;
}t_struct;

extern t_struct main_data;


//printing staff
void	print_title(void);
void	init_title(void);
int	ft_putint(int c);

//signals staff
void handler (int status);

//cursor staff
void	moveback_cursor(void);

//history staff
void take_history(void);
void numerate_history(t_list *history);

//ESC commands staff
int key_control(char *str);
int escape_up(char *str);
int escape_down(char *str);
int escape_left(char *str);
int	escape_right(char *str);
int	escape_backspace(char *str);
int escape_ctrl(char *str);

//parser staff
char *parser(char *str, char **env);

//list utils staff
void	fill_id(t_list **head);
void	init_commands(void);
void	fill_commands(char *cmd, int cntr);
void	fill_flag(char *flag);


#endif
