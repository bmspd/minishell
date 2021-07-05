#include "libft.h"

void	ft_putstr(char *string)
{
	while (*string)
	{
		ft_putchar(*string);
		string++;
	}
}
