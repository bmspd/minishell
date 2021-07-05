#include "libft.h"

int	search_n(char *current)
{
	int	i;

	i = 0;
	if (!current)
		return (0);
	while (current[i] != '\0')
	{
		if (current[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
