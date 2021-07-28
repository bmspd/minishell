
#include "../includes/minishell.h"
t_struct	g_main_data;

int main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	init_title();
	init_variables();

	g_main_data.list_envp = create_list_envp(env);
	external_history();
	set_terminal(1);
	if (g_main_data.ws.ws_col >= 106)
		print_big_greeting();
	else if (g_main_data.ws.ws_col < 106)
		print_small_greeting();

	while (10)
	{
		print_title();
		g_main_data.buf_hist = ft_strdup("");
		typing_cycle();
		if(!ft_strncmp("exit", g_main_data.buf_hist, 6) || !ft_strncmp("\4", g_main_data.buf_hist, 2))
			break;
		if (ft_strncmp(g_main_data.buf_hist, "", 2))
			main_engine();
		else
			free(g_main_data.buf_hist);

	}
	set_terminal(0);
	write(1, "💔💔💔 \x1b[36msee ya later \x1b[31m↻\x1b[0m\n",
		  ft_strlen("💔💔💔 \x1b[36msee ya later \x1b[31m↻\x1b[0m\n"));
	return (0);
}
