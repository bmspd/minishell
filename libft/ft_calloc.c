#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*mem;
	size_t			i;

	i = 0;
	mem = malloc(count * size);
	if (!mem)
		return (0);
	while (i < (count * size))
	{
		mem[i] = 0;
		i++;
	}
	return ((void *)mem);
}
