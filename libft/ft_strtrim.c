#include "libft.h"

static int	check(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (0);
		i++;
	}
	return (1);
}

static size_t	start_symb(char const *s1, char const *set)
{
	size_t	start;
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	start = 0;
	while (s1[i])
	{
		if (check(s1[i], set))
			break ;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				start++;
				break ;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (start);
}

static size_t	end_symb(char const *s1, char const *set)
{
	size_t	end;
	size_t	j;
	size_t	i;

	i = ft_strlen(s1) - 1;
	end = ft_strlen(s1);
	j = 0;
	while (i > 0)
	{
		if (check(s1[i], set))
			break ;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				end--;
				break ;
			}
			j++;
		}
		j = 0;
		i--;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*trimmed;

	if (!s1)
		return (0);
	start = start_symb(s1, set);
	end = end_symb(s1, set);
	i = 0;
	if (start > end)
	{
		start = 0;
		end = 0;
	}
	trimmed = malloc((end - start + 1) * sizeof(char));
	if (!trimmed)
		return (0);
	while (start < end)
	{
		trimmed[i++] = s1[start++];
	}
	trimmed[i] = '\0';
	return (trimmed);
}
