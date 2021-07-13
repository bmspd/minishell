
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
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct s_ENV
{
	char		*name;
	char		*value;
	struct s_ENV	*next;
	
}				ENV;

typedef struct s_struct{
	t_list *history;
	int	history_id;
	int hist_flag;
	int null_flag;
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
	int key_amount;
	int temp_key_amount;
	char **env0;
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
void parser(char *str, char **env);

//list utils staff
void	fill_id(t_list **head);
void	init_commands(void);
void	fill_commands(char *cmd, int cntr);
void	fill_flag(char *flag);

//create envp_list and cd and unset
ENV		*create_list_envp(char **envp);
void	env(ENV *list);
ENV		*new_envp(char	*env, ENV	*old);
ENV		*find_VAR_ENV(ENV *list_envp, char *VAR);
void	rem_envp_VAR(ENV **list_envp, char *VAR);
void	go_to_direction(char *path_dir, ENV *list_envp);
char	*get_pwd(void);
void	print_pwd(void);
size_t	count_arr(char **arr);
void	lastadd_ENV_VAR(ENV *list_envp, ENV *last);
#endif
