#include "../includes/minishell.h"

char	*tolower_str(char *str)
{
	size_t size;
	size_t i;

	i = 0;
	size = ft_strlen(str);
	while (i < size)
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

void	error_massege_fd(int fd, char *name_file)
{
	char	*str_error;

	if (fd == -1)
	{
		write(2, "minishell: ", 12);
		str_error = strerror(errno);
		str_error = ft_strdup(str_error);
		str_error = tolower_str(str_error);
		write(2, str_error, ft_strlen(str_error));
		write(2, ": ", 2);
		write(2, name_file, ft_strlen(name_file));
		write(2, "\n", 1);
	}
}

int	open_rdfile(char *name_file)
{
	int fd;

	fd = open(name_file, O_RDONLY);
	error_massege_fd(fd, name_file);
	return (fd);
}

int	open_addfile(char *name_file)
{
	int fd;

	fd = open(name_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	error_massege_fd(fd, name_file);
	return (fd);
}

int	open_trfile(char *name_file)
{
	int fd;

	fd = open(name_file, O_CREAT | O_WRONLY  | O_TRUNC, 0644);
	error_massege_fd(fd, name_file);
	return (fd);
}
