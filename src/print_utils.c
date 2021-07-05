#include "../includes/minishell.h"
void init_title(void)
{
//	main_data.title = ft_strdup("\x1b[31m🔥🔥🔥 minishell \x1b[36m➜ \x1b[0m");
	main_data.title = ft_strdup("minishell $ ");
	main_data.title_length = (int)ft_strlen(main_data.title);
}

void	print_title(void)
{
	write(STDOUT_FILENO, main_data.title, main_data.title_length);
}