#include "../includes/minishell.h"

int	count_file_direction(const char *path)
{
	int				i;
	DIR				*dir;
	struct dirent	*file;

	dir = opendir(path);
	if (!dir)
		return (0);
	i = 0;
	file = readdir(dir);
	i++;
	while (file)
	{
		file = readdir(dir);
		i++;
	}
	closedir(dir);
	return (i);
}

char	**creat_arr(int count)
{
	char	**out;

	if (!count)
		return (NULL);
	out = malloc(sizeof(char *) * (count + 1));
	return (out);
}

char	**free_error_getlf(int i, DIR *dir, char *pwd, char **out_list)
{
	if (i > 0)
		free(pwd);
	if (i > 1)
		closedir(dir);
	if (i > 2)
		free_arr(out_list, count_arr(out_list));
	return (NULL);
}

char	**write_in_lf(char **out_list, DIR *dir, char *pwd)
{
	struct dirent	*file;
	int				i;

	i = 0;
	file = readdir(dir);
	out_list[i] = ft_strdup(file->d_name);
	if (!out_list[i])
		return (free_error_getlf(3, dir, pwd, out_list));
	i++;
	while (file)
	{
		file = readdir(dir);
		if (!file)
			break ;
		out_list[i] = ft_strdup(file->d_name);
		if (!out_list[i])
			return (free_error_getlf(3, dir, pwd, out_list));
		i++;
	}
	out_list[i] = NULL;
	return (out_list);
}

char	**create_list_file(void)
{
	DIR		*dir;
	char	*pwd;
	char	**out_list;

	pwd = get_pwd();
	if (!pwd)
		return (NULL);
	dir = opendir(pwd);
	if (!dir)
		return (free_error_getlf(1, dir, pwd, out_list));
	out_list = creat_arr(count_file_direction(pwd));
	if (!out_list)
		return (free_error_getlf(2, dir, pwd, out_list));
	out_list = write_in_lf(out_list, dir, pwd);
	if (!out_list)
		return (NULL);
	closedir(dir);
	free(pwd);
	return (out_list);
}
