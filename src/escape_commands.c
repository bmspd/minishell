#include "../includes/minishell.h"

int	key_control(char *str)
{
	if (escape_up(str))
		return (1);
	else if (escape_down(str))
		return (2);
	else if (escape_left(str))
		return (3);
	else if (escape_right(str))
		return (4);
	else if (escape_backspace(str))
		return (5);
	else if (escape_ctrl(str))
		return (6);
	else if (escape_tab(str))
		return (7);
	else if (ignore_escape(str))
		return (8);
	return (0);
}
