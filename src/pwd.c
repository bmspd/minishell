#include "../includes/minishell.h"

char	*get_pwd(void)
{
	char	*pwd;
	char	*chek;
	int		nb;

	nb = 100;
	pwd = ft_calloc(sizeof(char), nb);
	if (!pwd)
		exit(42);
	chek = getcwd(pwd, nb);
	nb += 255;
	while (!chek)
	{
		free(pwd);
		pwd = ft_calloc(sizeof(char), nb);
		if (!pwd)
			exit(42);
		chek = getcwd(pwd, nb);
		nb += 255;
	}
	return (pwd);
}

void	print_pwd(int fd)
{
	char	*tmp;

	tmp = get_pwd();
	write(fd, tmp, ft_strlen(tmp));
	write(fd, "\n", 1);
	free(tmp);
}

size_t	count_arr(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}
