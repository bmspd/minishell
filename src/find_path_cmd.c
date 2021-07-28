#include "../includes/minishell.h"

int	look_in_direction(char *path, char *find_file)
{
	DIR				*direction;
	struct dirent	*file;

	file = NULL;
	direction = opendir(path);
	if (direction)
		file = readdir(direction);
	while (file)
	{
		if (!ft_strncmp(find_file, file->d_name, ft_strlen(find_file) + 1))
		{
			closedir(direction);
			return (1);
		}
		file = readdir(direction);
	}
	if (direction)
		closedir(direction);
	return (0);
}

void	addhomedir(char **paths)
{
	int		i;
	char	*tmp;
	t_envp	*home;

	i = 0;
	home = find_var_envp(g_main_data.list_envp, "HOME");
	while (paths[i])
	{
		if (!ft_strncmp(paths[i], "~", 1))
		{
			if (!home)
				break ;
			tmp = paths[i];
			paths[i] = ft_strjoin(home->value, ft_strchr(tmp, '/'));
			free(tmp);
		}
		i++;
	}
}

char	*out_path(char **paths, char *tmp_name)
{
	char	*out;
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		if (look_in_direction(paths[i], tolower_str(tmp_name)))
		{
			tmp = ft_strjoin("/", tmp_name);
			out = ft_strjoin(paths[i], tmp);
			free(tmp);
			free(tmp_name);
			free_arr(paths, count_arr(paths));
			return (out);
		}
		i++;
	}
	free(tmp_name);
	free_arr(paths, count_arr(paths));
	return (NULL);
}

char	*find_path_cmd(char *value, char *name_prog)
{
	char	**paths;
	char	*tmp_name;

	tmp_name = ft_strdup(name_prog);
	if (!tmp_name)
		return (NULL);
	if (!value)
		return (NULL);
	paths = ft_split(value, ':');
	if (!paths)
	{
		free(tmp_name);
		return (NULL);
	}
	addhomedir(paths);
	return (out_path(paths, tmp_name));
}
