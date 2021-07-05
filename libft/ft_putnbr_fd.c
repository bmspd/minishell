#include "libft.h"

static void	printing(int n, int fd)
{
	char	c;

	if (n >= 10)
	{
		printing(n / 10, fd);
		printing(n % 10, fd);
	}
	else
	{
		c = n + '0';
		write(fd, &c, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = -n;
		}
		printing(n, fd);
	}
}
