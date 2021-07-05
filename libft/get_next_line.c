#include "libft.h"

static char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	char			*join;
	unsigned int	sumlen;
	size_t			i;
	size_t			j;
	unsigned int	len1;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(s2));
	len1 = ft_strlen(s1);
	sumlen = len1 + ft_strlen(s2);
	join = malloc((sumlen + 1) * sizeof(char));
	if (!join)
		return (0);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = '\0';
	return (join);
}

static char	*moving_pointer(char *old_string)
{
	char	*new_string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!old_string)
		return (0);
	while (old_string[i] != '\0' && old_string[i] != '\n')
		i++;
	if (!old_string[i])
	{
		free(old_string);
		return (0);
	}
	new_string = malloc(sizeof(char) * ((ft_strlen(old_string) - i) + 1));
	if (!new_string)
		return (0);
	i++;
	while (old_string[i] != '\0')
		new_string[j++] = old_string[i++];
	new_string[j] = '\0';
	free(old_string);
	return (new_string);
}

static char	*write_to_delim(char *current)
{
	char	*line;
	int		i;

	i = 0;
	while (current[i] != '\n' && current[i] != '\0')
	{
		i++;
	}
	line = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (current[i] != '\n' && current[i] != '\0')
	{
		line[i] = current[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static int	what_to_return(int reading)
{
	if (reading == 0)
		return (0);
	return (1);
}

int	get_next_line(int fd, int buff_size, char **line)
{
	static char	*current[10000];
	char		*buff;
	int			reading;

	reading = 1010;
	if (buff_size < 1 || fd < 0 || fd > 10000 || !line)
		return (-1);
	buff = (char *)malloc(sizeof(char) * (buff_size + 1));
	if (!buff)
		return (-1);
	while (!search_n(current[fd]) && reading != 0)
	{
		reading = read(fd, buff, buff_size);
		if (reading == -1)
		{
			free(buff);
			return (-1);
		}
		buff[reading] = '\0';
		current[fd] = ft_strjoin_gnl(current[fd], buff);
	}
	free(buff);
	*line = write_to_delim(current[fd]);
	current[fd] = moving_pointer(current[fd]);
	return (what_to_return(reading));
}
