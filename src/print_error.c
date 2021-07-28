#include "../includes/minishell.h"

void	error_massage_exec(char *name_file)
{
	char	*str_error;

	write(2, "minishell: ", 12);
	str_error = strerror(errno);
	str_error = ft_strdup(str_error);
	str_error = tolower_str(str_error);
	write(2, str_error, ft_strlen(str_error));
	write(2, ": ", 2);
	write(2, name_file, ft_strlen(name_file));
	write(2, "\n", 1);
	exit(126);
}

void	not_found(t_cmd *cmd)
{
	write(2, "minishell: ", 12);
	write(2, cmd->name, ft_strlen(cmd->name));
	write(2, ": command not found\n", 21);
}

void	print_error(char *cmd, char *arg)
{
	char	*error;

	error = strerror(errno);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, ": ", 2);
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
}
