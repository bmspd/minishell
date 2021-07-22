
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
	int null_flag;
	char *buf_hist;
	char *title;
	int	title_length;
	int cursor_place;
	struct winsize ws;
	t_list *commands;
	int flag1;
	int counter;
	int key_amount;
	char *term_name;
	struct termios term;
	int current_tab;
	char	*part;
	char	*old_buf_hist;
	int	buf_flag;
	ENV *list_envp;
}t_struct;

extern t_struct main_data;

//printing staff
void	print_title(void);
void	init_title(void);
int	ft_putint(int c);
void	print_big_greeting(void);
void	print_small_greeting(void);

//signals staff
void handler (int status);
void handler1 (int status);
void set_terminal(int type);

//cursor staff
void	moveback_cursor(void);

//history staff
void take_history(void);
void numerate_history(t_list *history);
t_list	*ft_lstnew_history(void *content, int amount);
int open_history(int flag);
void external_history();
void fill_external_history(int fd);


//ESC commands staff
int key_control(char *str);
int escape_up(char *str);
int escape_down(char *str);
int escape_left(char *str);
int	escape_right(char *str);
int	escape_backspace(char *str);
int escape_ctrl(char *str);
int	escape_tab(char *str);

//AUTOCOMPLETE UTILS
int	check_list_file(char **list_file, int len);
int	find_index(char **list_file, int len, char *list_elem);
int buf_or_old_buf_hist(char *hist);
int	take_word_part(void);
void no_buff_case(char **list_files, int len);
int    fill_index_take_length(int  *index, char **list_files, int len, char *list_elem);
char    *choose_list_elem(char **list_files, int len, char *list_elem, int z);
void    autocomplete(char *list_elem, int i);
void    is_buff_case(char **list_files, int len, char **list_elem, int i);
void    if_zero_current_tab(void);

//parser staff
void space(char *str, int *i, int *j);
void parser(char *str);
char *dollar(char *str, int *i);
char *solo_quote(char *str, int *i);
char *slash(char *str, int *i);
char	*double_quote(char *str, int *i);

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
void	free_arr(char **arr, int count);

//Вот тебе функция обезьянна не бритая
char	**create_list_file(void);
void	free_arr(char **arr, int count);

//heredoc
int		*heredoc(char *stop_word);

//memory staff
void    safe_free(char *element);

//Convertation list to char
char **list_to_char(void);
int count_elements(void);
char **list_to_help_char(void);

//builtin staff
void	builtin_echo(char **arguments, int fd);
#endif
