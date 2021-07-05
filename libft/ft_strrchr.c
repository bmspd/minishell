#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*str;
	unsigned char	symb;
	size_t			len;

	len = 0;
	str = (unsigned char *)s;
	symb = (unsigned char)c;
	while (*str)
	{
		len++;
		str++;
	}
	while (len + 1 > 0)
	{
		if (*str == symb)
			return ((char *)str);
		str--;
		len--;
	}
	return (0);
}
