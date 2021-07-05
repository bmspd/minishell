#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;
	size_t	j;
	size_t	res;

	j = 0;
	dstlen = 0;
	srclen = 0;
	res = 0;
	while (dst[dstlen])
		dstlen++;
	while (src[srclen])
		srclen++;
	if (dstsize > dstlen)
		res = srclen + dstlen;
	else
		res = srclen + dstsize;
	i = dstlen;
	if (dstlen < dstsize - 1 && dstsize > 0)
		while (src[j] && dstlen + j < dstsize - 1)
			dst[i++] = src[j++];
	dst[i] = '\0';
	return (res);
}
