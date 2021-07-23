#include "../includes/minishell.h"

static int	break_condition(char *str)
{
	if (!ft_strncmp("\4", str, 2) && (!ft_strncmp("\4", str, 2)
			&& !ft_strncmp("", main_data.buf_hist, 2)))
	{
		safe_free(main_data.buf_hist);
		main_data.buf_hist = ft_strdup("\4");
		write(1, "exit\n", 6);
		return (1);
	}
	if (!ft_strncmp("\n", str, 2))
	{
		return (1);
	}
	return (0);
}

void	typing_cycle(void)
{
	char	str[2000];
	int		l;

	while (10)
	{
		l = read(0, str, 2000);
		str[l] = 0;
		if (key_control(str))
			;
		else
		{
			if (ft_strncmp("\4", str, 2))
			{
				write(1, str, l);
				main_data.key_amount++;
				if (ft_strncmp("\n", str, 2))
					symbol_not_enter(str);
			}
		}
		if (break_condition(str))
			break ;
	}
}

void    symbol_not_enter(char *str)
{
	char    *tmp0;
	char    *tmp1;
	char    *tmp2;

	safe_free(main_data.part);
	main_data.part = NULL;
	main_data.current_tab = 0;
	main_data.buf_flag = 0;
	tmp0 = ft_substr(main_data.buf_hist, 0, main_data.cursor_place);
	tmp1 = ft_strjoin(tmp0, str);
	tmp2 = ft_substr(main_data.buf_hist, main_data.cursor_place,
					 ft_strlen(main_data.buf_hist) - main_data.cursor_place);
	free(main_data.buf_hist);
	main_data.buf_hist = ft_strjoin(tmp1, tmp2);
	//if (ft_strncmp("\4", str, 2))
	main_data.cursor_place += (int)ft_strlen(str);
	write(1, tmp2, ft_strlen(tmp2));
	if (main_data.cursor_place != ft_strlen(main_data.buf_hist))
	{
		int z = 0;
		while (z < ft_strlen(tmp2))
		{
			tputs(cursor_left, 1, ft_putint);
			z++;
		}
	}
	main_data.history_id = -1;
	free(tmp0);
	free(tmp2);
	free(tmp1);
}
