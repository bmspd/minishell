#include "../includes/minishell.h"

static void	n_mode(char **arguments, int fd, int len)
{
	int	i;

	i = 1;
	if (!arguments[i])
		return ;
	while (i < len)
	{
		write(fd, arguments[i], ft_strlen(arguments[i]));
		if (i == len - 1)
			write(fd, "\033[30;48;2;229;229;229m%\033[0m\n",
				  ft_strlen("\033[30;48;2;229;229;229m%\033[0m\n"));
		else
			write(fd, " ", 1);
		i++;
	}
}

void	builtin_echo(char **arguments, int fd)
{
	int	i;
	int	len;

	len = (int)count_arr(arguments);
	i = 0;
	if (!arguments[i])
	{
		write(fd, "\n", 1);
		return ;
	}
	if (!ft_strncmp("-n", arguments[i], 3))
	{
		n_mode(arguments, fd, len);
		return ;
	}
	while (i < len)
	{
		write(fd, arguments[i], ft_strlen(arguments[i]));
		if (i == len - 1)
			write(fd, "\n", 1);
		else
			write(fd, " ", 1);
		i++;
	}
}
