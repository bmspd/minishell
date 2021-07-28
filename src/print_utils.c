#include "../includes/minishell.h"

int	ft_putint(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

void	init_title(void)
{
	g_main_data.title = ft_strdup("\x1b[31m🔥🔥🔥 minishell \x1b[36m➜ \x1b[0m");
	g_main_data.title_length = (int)ft_strlen(g_main_data.title);
	g_main_data.title_cursor_positions = 16;
}

void	print_title(void)
{
	write(STDOUT_FILENO, g_main_data.title, g_main_data.title_length);
}

void	print_big_greeting(void)
{
	char	*picture;

	picture = "      ____                           "
		  "__    __     __         __     __  __     ______\n"
		  "     /___/\\_                        /\\ \"-./  \\   /\\ \\      "
		  " /\\ \\   /\\ \\/ /    /\\__  _\\     \n"
		  "    _\\   \\/_/\\__                    \\ \\ \\-./\\ \\  \\ \\ \\____ "
		  " \\ \\ \\  \\ \\  _\"-.  \\/_/\\ \\/     \n"
		  "  __\\       \\/_/\\                    \\ \\_\\ \\ \\_\\  \\ \\"
		  "_____\\  \\ \\_\\  \\ \\_\\ \\_\\    \\ \\_\\   \n"
		  "  \\   __    __ \\ \\                    \\/_/  \\/_/   \\/_____/ "
		  "  \\/_/   \\/_/\\/_/     \\/_/   \n __\\  \\_\\   \\_\\ \\ \\   __ \n"
		  "/_/\\\\   __   __  \\ \\_/_/\\            __         __ "
		  "   __     __  __     __  __     __   __     ______   \n"
		  "\\_\\/_\\__\\/\\__\\/\\__\\/_\\_\\/           /\\ \\       "
		  "/\\ \"-./  \\   /\\ \\_\\ \\   /\\ \\/\\ \\   /\\ \"-.\\ \\   /\\  ___\\   \n"
		  "   \\_\\/_/\\       /_\\_\\/             \\ \\ \\____  \\ \\ \\-./\\ \\  \\ "
		  "\\____ \\  \\ \\ \\_\\ \\  \\ \\ \\-.  \\  \\ \\ \\__ \\ \n"
		  "      \\_\\/       \\_\\/                \\ \\_____\\  \\ \\_\\ \\ \\_\\ "
		  " \\/\\_____\\  \\ \\_____\\  \\ \\_\\\\\"\\_\\  \\ \\_____\\ \n"
		  "                                      \\/_____/   \\/_/  \\/_/  "
		  " \\/_____/   \\/_____/   \\/_/ \\/_/   \\/_____/\n\n";
	write(1, GREEN, ft_strlen(GREEN));
	write(1, picture, ft_strlen(picture));
	write(1, CLR_RESET, ft_strlen(CLR_RESET));
}

void	print_small_greeting(void)
{
	char	*picture;

	picture = "      ____  \n"
		  "     /___/\\_   \n"
		  "    _\\   \\/_/\\__  \n"
		  "  __\\       \\/_/\\  \n"
		  "  \\   __    __ \\ \\    \n"
		  " __\\  \\_\\   \\_\\ \\ \\   __   \n"
		  "/_/\\\\   __   __  \\ \\_/_/\\   \n"
		  "\\_\\/_\\__\\/\\__\\/\\__\\/_\\_\\/ \n"
		  "   \\_\\/_/\\       /_\\_\\/ \n"
		  "      \\_\\/       \\_\\/ \n\n";
	write(1, GREEN, ft_strlen(GREEN));
	write(1, picture, ft_strlen(picture));
	write(1, CLR_RESET, ft_strlen(CLR_RESET));
}
