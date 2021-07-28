SRCS			= 	main.c print_utils.c signals.c cursor_utils.c escape_commands.c history.c \
					escape_keys.c escape_keys2.c parser.c cmd_list_utils.c\
					create_list_envp.c cd.c create_list_file.c mem_utils.c \
					list_to_char.c escape_backspace.c escape_tab_utils1.c \
					escape_tab_utils2.c heredoc.c parser_utils1.c parser_utils2.c \
					new_addfile.c escape_keys3.c\
					new_block.c new_heredoc.c new_rdfile.c new_trfile.c\
					pipex.c write_info_pipe_block.c create_pipe_block.c\
					new_cmd.c get_fd.c open_files.c\
					parser_utils3.c history_file.c built_in1.c extra_parser.c \
					main_cycle1.c main_cycle2.c export.c print_error.c\
					reg_last_exec.c read_block.c builtin.c unset.c\
					find_path_cmd.c convert_list_in_arr.c env.c pwd.c\
					utils_cd.c print_export.c
DIR_S			= src
SOURCE			=$(addprefix $(DIR_S)/,$(SRCS))
OBJS			= $(SOURCE:.c=.o)
HEADER			= ./includes/minishell.h
CC				= gcc
RM				= rm -f
CFLAGS			= -I $(HEADER) -Wall -Werror -Wextra

NAME			= minishell

all:			$(NAME)

%.o:		%.c $(HEADER)
				@printf "\033[0;35mGenerating MINISHELL objects... %-33.33s\r" $@
				@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):		$(OBJS)
				@make -C ./libft/
				@echo "\033[0;32mMaking MINISHELL..."
				@printf "༼ ༎ຶ ෴ ༎ຶ༽\t"
				@sleep 0.5
				@printf "༼ ༎ຶ ෴ ༎ຶ༽\t"
				@sleep 0.5
				@printf "༼ ༎ຶ ෴ ༎ຶ༽\n"
				@sleep 0.5
				@$(CC) -o $(NAME )$@ $^ -ltermcap -Llibft -lft
				@echo "\033[0mAlmost done !"
				@printf "(｡◕‿‿◕｡)\t"
				@sleep 0.5
				@printf "(｡◕‿‿◕｡)\t"
				@sleep 0.5
				@printf "(｡◕‿‿◕｡)\nDone!\n"
clean:
				@echo "\033[0;31mDeleting MINISHELL objects..."
				@sleep 0.5
				@$(RM) $(OBJS)
				@echo "\033[0;31mCleaning LIBFT..."
				@sleep 0.5
				@make -C ./libft/ clean
				@echo "\033[0mDone!"

fclean:			clean
				@echo "\033[0;31mDeleting MINISHELL executable..."
				@sleep 0.5
				@$(RM) $(NAME)
				@sleep 0.5
				@echo "\033[0;31mCleaning LIBFT..."
				@sleep 0.5
				@make -C ./libft/ fclean
				@echo "\033[0mDone!"
re:				fclean all

debug:
	gcc -g ${SOURCE} ./libft/*.c -ltermcap -o ${NAME}

.PHONY:			all clean fclean re debug