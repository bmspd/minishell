#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*join;
	unsigned int	sumlen;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	sumlen = ft_strlen(s1) + ft_strlen(s2);
	join = malloc((sumlen + 1) * sizeof(char));
	if (!join)
		return (0);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = '\0';
	return (join);
}
