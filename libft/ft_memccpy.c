#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*tdst;
	unsigned char	*tsrc;
	unsigned char	symb;

	i = 0;
	symb = (unsigned char)c;
	tdst = (unsigned char *)dst;
	tsrc = (unsigned char *)src;
	while (i < n)
	{
		tdst[i] = tsrc[i];
		dst++;
		if (symb == tsrc[i])
		{
			return (dst);
		}
		 i++;
	}
	return (0);
}
