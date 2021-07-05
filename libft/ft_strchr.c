#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*str;
	unsigned char	symb;

	str = (unsigned char *)s;
	symb = (unsigned char)c;
	while (*str != '\0')
	{
		if (*str == symb)
			return ((char *)str);
		str++;
	}
	if (*str == symb)
		return ((char *)str);
	return (0);
}
