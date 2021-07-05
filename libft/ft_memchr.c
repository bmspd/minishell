#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp;
	unsigned char	symb;
	size_t			i;

	i = 0;
	temp = (unsigned char *)s;
	symb = (unsigned char)c;
	while (i < n)
	{
		if (*temp == symb)
			return (temp);
		temp++;
		i++;
	}
	return (0);
}
