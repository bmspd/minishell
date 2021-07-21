SRCS			= 	main.c print_utils.c signals.c cursor_utils.c escape_commands.c history.c \
					escape_keys.c escape_keys2.c parser.c cmd_list_utils.c\
					create_list_envp.c cd.c create_list_file.c mem_utils.c \
					list_to_char.c escape_backspace.c escape_tab_utils1.c \
					escape_tab_utils2.c heredoc.c parser_utils1.c parser_utils2.c \
					parser_utils3.c
DIR_S			= src
SOURCE			=$(addprefix $(DIR_S)/,$(SRCS))
OBJS			= $(SOURCE:.c=.o)
HEADER			= ./includes/minishell.h
CC				= gcc
RM				= rm -f
CFLAGS			= -I $(HEADER) #-Wall -Werror -Wextra

NAME			= minishell

all:			$(NAME)

%.o:		%.c $(HEADER)
		$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):		$(OBJS)
				make -C ./libft/
				$(CC) -o $(NAME )$@ $^ -ltermcap -Llibft -lft

clean:
				$(RM) $(OBJS)
				make -C ./libft/ clean

fclean:			clean
				$(RM) $(NAME)
				make -C ./libft/ fclean

re:				fclean all

debug:
	gcc -g ${SOURCE} ./libft/*.c -ltermcap -o ${NAME}

.PHONY:			all clean fclean re