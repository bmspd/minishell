
#ifndef MINISHELL_H
#define MINISHELL_H

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define CLR_RESET   "\x1b[0m"


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
	char *title;
	int	title_length;
	int abs_col;
	int	abs_line;
	struct winsize ws;
}t_struct;

extern t_struct main_data;



void	print_title(void);
void	init_title(void);

#endif
