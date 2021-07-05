#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tdst;
	unsigned char	*tsrc;
	size_t			i;

	i = 0;
	tdst = (unsigned char *)dst;
	tsrc = (unsigned char *)src;
	if (src == (void *)0 && dst == (void *)0)
		return ((void *)0);
	if (tsrc < tdst)
	{
		while (len > 0)
		{
			len--;
			tdst[len] = tsrc[len];
		}
	}
	else
	{
		while (i++ < len)
			*tdst++ = *tsrc++;
	}
	return (dst);
}
