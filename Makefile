SRCS			= 	main.c print_utils.c signals.c cursor_utils.c escape_commands.c history.c \
					escape_keys.c escape_commands2.c
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

.PHONY:			all clean fclean re