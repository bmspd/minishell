#include "../includes/minishell.h"

void	safe_free(char *element)
{
	if (element)
		free(element);
}
