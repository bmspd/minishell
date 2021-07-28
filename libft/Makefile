SRCS			=	ft_bzero.c ft_memccpy.c ft_memchr.c ft_memcpy.c \
					ft_memmove.c ft_memset.c ft_tolower.c ft_toupper.c \
					ft_isprint.c ft_isascii.c ft_isalnum.c ft_isdigit.c \
					ft_isalpha.c ft_atoi.c ft_strncmp.c ft_strnstr.c \
					ft_strrchr.c ft_strchr.c ft_strlcat.c ft_strlcpy.c \
					ft_strlen.c ft_memcmp.c ft_calloc.c ft_strdup.c \
					ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
					ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c \
					ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c \
					ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
					ft_lstsize.c ft_lstlast.c ft_lstmap.c search_n.c \
					get_next_line.c ft_putchar.c ft_putstr.c malloc_x.c
OBJS			= $(SRCS:.c=.o)
HEADER			= libft.h
%.o:		%.c $(HEADER)
		@printf "\033[0;36mGenerating LIBFT objects... %-33.33s\r" $@
		@$(CC) $(CFLAGS) -c -o $@ $<
CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I $(HEADER)

NAME			= libft.a

all:			$(NAME) 

$(NAME):		$(OBJS)
				@echo "\n"
				@echo "Making libft.a"
				@sleep 0.5
				@printf "୧༼ಠ益ಠ༽୨\t"
				@sleep 0.5
				@printf "୧༼ಠ益ಠ༽୨\t"
				@sleep 0.5
				@printf "୧༼ಠ益ಠ༽୨\n"
				@sleep 0.5
				@ar rcs $(NAME) $(OBJS)

clean:
				@echo "\033[0;31mDeleting LIBFT objects...\033[0m"
				@sleep 0.5
				@$(RM) $(OBJS)
fclean:			clean
				@echo "\033[0;31mDeleting LIBFT library...\033[0m"
				@sleep 0.5
				@$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re