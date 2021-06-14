SRCS	=	$(DIR)/init.c \
			$(DIR)/lil_atoi.c \
			$(DIR)/philosopher.c \
			$(DIR)/print_message.c \
			$(DIR)/monitor.c \
			$(DIR)/time.c

DIR		=	./srcs

INCLUDE	=	-I .

OBJS	:=	$(SRCS:.c=.o)

CC		=	clang

CFLAGS	=	-Wall -Wextra -Werror -pthread #-g3 -fsanitize=thread

FSAN	=	-g3 -fsanitize=address

NAME	=	philo

all		:	$(NAME)

$(NAME)	:	$(OBJS) main.c
			$(CC) $(CFLAGS) main.c $(OBJS) $(INCLUDE) -o $(NAME)

fsan	:	$(OBJS) main.c
			$(CC) $(CFLAGS) $(FSAN) main.c $(OBJS) $(INCLUDE) -o $(NAME)

leaks	:	$(NAME)
			valgrind --tool=memcheck --track-origins=yes --leak-check=full --leak-resolution=high --show-reachable=yes
clean	:
			rm -rf $(OBJS)

fclean	:	clean
			rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all fsan clean fclean re