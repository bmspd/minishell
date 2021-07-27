
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
#define	 COMAND		0
#define	 ARGV		1
#define	 HEREDOC	2
#define	 RDFILE		3
#define	 WRFILEADD	4
#define	 WRFILETR	5
#define	 PIPE		6
#define STDIN	0
#define STDOUT	1
#define ENV		1
#define CD		2
#define PWD		3
#define MYECHO	4
#define UNSET	5
#define EXPORT	6

typedef struct s_file_read
{
	char	*name_file;
	int		order;
	struct s_file_read *next;
}				t_rdfile;

typedef struct s_heredoc
{
	char	*stop_word;
	int		fd;
	int		order;
	struct s_heredoc *next;
}				t_heredoc;

typedef struct s_file_write_add
{
	char	*name_file;
	int		order;
	struct s_file_write_add *next;
}				t_addfile;

typedef struct s_file_write_tr
{
	char	*name_file;
	int		order;
	struct s_file_write_tr *next;
}				t_trfile;


typedef struct	s_cmd
{
	int	in;
	int	out;
	char *name;	
	char **arg;
	char **env;
}				t_cmd;

typedef struct s_block
{
	t_cmd			*cmd;
	t_rdfile		*rdfile;
	t_heredoc		*heredoc;
	t_trfile		*trfile;
	t_addfile		*addfile;
	pid_t			pid;
	int				order;
	struct s_block	*next;
}				t_block;

typedef struct s_envp
{
	char		*name;
	char		*value;
	struct s_envp	*next;

}				t_envp;

typedef struct s_struct{
	t_list *history;
	int	history_id;
	int null_flag;
	char *buf_hist;
	char *title;
	int	title_length;
	int title_cursor_positions;
	int cursor_place;
	struct winsize ws;
	t_list *commands;
	int flag1;
	int counter;
	int key_amount;
	char *term_name;
	struct termios term;
	int current_tab;
	int	exit_status;
	char	*part;
	char	*old_buf_hist;
	int	buf_flag;
	t_envp *list_envp;
	t_envp *sorted_list_envp;
	int new_cmd_flag;
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
int	check_ascii(void);
void cursor_behaviour(char *tmp2);

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
int	ignore_escape(char *str);

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
int extra_parser(void);
char	*delete_spaces_behind(char *str);

//list utils staff
void	fill_id(t_list **head);
void	init_commands(void);
void	fill_commands(char *cmd, int cntr);
void	fill_flag(char *flag);

//create envp_list and cd and unset
t_envp		*create_list_envp(char **envp);
void	env(t_envp *list, int fd);
t_envp		*new_envp(char	*env, t_envp	*old);
t_envp		*find_var_envp(t_envp *list_envp, char *VAR);
void	rem_envp_VAR(t_envp **list_envp, char *VAR);
void	go_to_direction(t_cmd *cmd, t_envp *list_envp);
char	*get_pwd(void);
void	print_pwd(int fd);
size_t	count_arr(char **arr);
void	lastadd_envp(t_envp *list_envp, t_envp *last);
void	free_arr(char **arr, int count);

//Вот тебе функция обезьянна не бритая
char	**create_list_file(void);
void	free_arr(char **arr, int count);

//heredoc
int		heredoc(char *stop_word);

//memory staff
void    safe_free(char *element);
void	cleaning_foo(void);

//Convertation list to char
char **list_to_char(void);
int count_elements(void);
char **list_to_help_char(void);

//builtin staff
void	builtin_echo(char **arguments, int fd);

//ft_realloc for arg
char	**ft_realloc(char **ptr, size_t size);
char	*tolower_str(char *str);
//heredoc_session
int		heredoc(char *stop_word);

// new elements
t_block		*new_block(void);
t_cmd		*new_cmd(char *name);
t_heredoc	*new_heredoc(char *stop_word, int order);
t_rdfile	*new_rdfile(char *name_file, int order);
t_trfile	*new_trfile(char *name_file, int order);
t_addfile	*new_addfile(char *name_file, int order);

//last_elem
void		heredoc_add_back(t_heredoc **lst, t_heredoc *new);
t_heredoc	*last_heredoc(t_heredoc *lst);

t_trfile	*last_trfile(t_trfile *lst);
void		trfile_add_back(t_trfile **lst, t_trfile *new);

t_rdfile	*last_rdfile(t_rdfile *lst);
void		rdfile_add_back(t_rdfile **lst, t_rdfile *new);

t_addfile	*last_addfile(t_addfile *lst);
void		addfile_add_back(t_addfile **lst, t_addfile *new);

t_block		*last_block(t_block *lst);
void		block_add_back(t_block **lst, t_block *new);

//create_pipe_block
t_block	*create_pipe_block(char **str, char **check);
char	**ft_realloc(char **ptr, size_t size);

int		get_index(char *str, char *check);
int		init_heredoc(t_heredoc **hdoc, char *stop_word, int order);
void	init_rdfile(t_rdfile **rdfile, char *name_file, int order);
void	init_addfile(t_addfile **addfile, char *name_file, int order);
void	init_trfile(t_trfile **trfile, char *name_file, int order);

//free_all_element_pipex_block
void	free_addfile(t_addfile	*addfile);
void	free_trfile(t_trfile *trfile);
void	free_rdfile(t_rdfile *rdfile);
void	free_heredoc(t_heredoc *heredoc);
void	free_cmd(t_cmd *cmd);
void	free_block(t_block *block);

//for_print_and_count
int		count_block(t_block *block);
void 	free_VAR(t_envp *);



//open_files
int		open_trfile(char *name_file);
int		open_addfile(char *name_file);
int		open_rdfile(char *name_file);
void	get_fd(t_block *block, t_cmd *cmd, int i);

//pipex
int		pipex(t_block *block, char **envp, int in);
char *find_path_cmd(char *value, char *name_prog, char *home);
//main cycle staff
void    symbol_not_enter(char *str);
void    typing_cycle(void);
void	init_variables(void);
void	command_launcher(void);
void	main_engine(void);

char **convert_list_in_arr(t_envp *list_envp);
void	exec_cmd(t_cmd *cmd, char **envp);
int		exec_builtin(t_cmd *cmd);
void	export(t_cmd *cmd, int fd);
int		ft_overlap(char *s1, char *s2);
void	reg_last_exec(t_cmd *cmd, t_block *block);
void	crash(void);
#endif