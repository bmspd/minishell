#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (s1[i])
	{
		len++;
		i++;
	}
	copy = malloc((len + 1) * (sizeof(char)));
	if (!copy)
	{
		return (0);
	}
	i = 0;
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
