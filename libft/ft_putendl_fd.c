#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;
	char	c;

	if (s)
	{
		c = '\n';
		len = ft_strlen(s);
		write(fd, s, len);
		write(fd, &c, 1);
	}
}
