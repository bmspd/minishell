#include "../includes/minishell.h"

int		count_file_direction(const char *path)
{
	int i;
	DIR	*dir;
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
	char **out;

	if (!count)
		return (NULL);
	out = malloc(sizeof(char *) * (count + 1));
	return (out);
}

char	**create_list_file(void)
{
	DIR	*dir;
	char *pwd;
	char **out_list;
	struct dirent *file;
	int i;

	i = 0;
	pwd = get_pwd();
	if (!pwd)
		return (NULL);
	dir = opendir(pwd);
	if (!dir)
	{
		return (NULL);
	}
	out_list = creat_arr(count_file_direction(pwd));
	if (!out_list)
	{
		return (NULL);
	}
	file = readdir(dir);
	out_list[i] = ft_strdup(file->d_name);
	if (!out_list[i])
	{
		free_arr(out_list, count_arr(out_list));
		return (NULL);
	}
	i++;
	while (file)
	{
		file = readdir(dir);
		if (!file)
			break;
		out_list[i] = ft_strdup(file->d_name);
		if (!out_list[i])
		{
			free_arr(out_list, count_arr(out_list));
			return (NULL);
		}
		i++;
	}
	out_list[i] = NULL;
	closedir(dir);
	free(pwd);
	return (out_list);
}