#include "libft.h"

void	*ft_memset(void *dest, int val, size_t num)
{
	size_t			i;
	unsigned char	*tdest;
	unsigned char	symb;

	symb = (unsigned char)val;
	tdest = (unsigned char *)dest;
	i = 0;
	while (i < num)
	{
		*tdest = symb;
		i++;
		tdest++;
	}
	return (dest);
}
