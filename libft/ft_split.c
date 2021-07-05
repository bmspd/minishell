#include "libft.h"

static size_t	words_count(char const *s, char c)
{
	size_t	counter;

	counter = 0;
	while (*s)
	{
		while (*s == c)
		{
			s++;
			if (*s == '\0')
				break ;
		}
		if (*s == '\0')
			break ;
		if (*s != c)
			counter++;
		while (*s != c)
		{
			s++;
			if (*s == '\0')
				break ;
		}
	}
	return (counter);
}

static size_t	word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		s++;
		len++;
	}
	return (len);
}

static char	*pass_delim(char const *s, char c)
{
	while (*s == c)
		s++;
	return ((char *)s);
}

static char	**allocate_error(char **split, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	if (!s)
		return (0);
	n = words_count(s, c);
	split = malloc((n + 1) * sizeof(char *));
	if (!split)
		return (0);
	while (i < n)
	{
		j = 0;
		s = pass_delim(s, c);
		split[i] = malloc ((word_len(s, c) + 1) * sizeof(char));
		if (!split[i])
			return (allocate_error(split, i));
		while (*s != c && *s != '\0')
			split[i][j++] = *s++;
		split[i++][j++] = '\0';
	}
	split[i] = 0;
	return (split);
}
