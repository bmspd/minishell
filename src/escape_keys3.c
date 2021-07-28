#include "../includes/minishell.h"

int	ignore_escape(char *str)
{
	if (!ft_strncmp("\e[2D", str, 5) || !ft_strncmp("\e[2A", str, 5)
		|| !ft_strncmp("\e[2B", str, 5) || !ft_strncmp("\e[2C", str, 5)
		|| (str[0] >= 0 && str[0] < 32 && str[0] != 10
			&& str[0] != 4))
	{
		write(1, "\a", 1);
		return (1);
	}
	return (0);
}
