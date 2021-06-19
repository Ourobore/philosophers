SRCS	=	$(DIR)/init.c \
			$(DIR)/lil_atoi.c \
			$(DIR)/philosopher.c \
			$(DIR)/threads.c \
			$(DIR)/print_message.c \
			$(DIR)/monitor.c \
			$(DIR)/time.c \
			$(DIR)/free.c

DIR		=	./srcs

INCLUDE	=	-I .

OBJS	:=	$(SRCS:.c=.o)

CC		=	clang

CFLAGS	=	-Wall -Wextra -Werror -pthread

NAME	=	philo

all		:	$(NAME)

$(NAME)	:	$(OBJS) main.c
			$(CC) $(CFLAGS) main.c $(OBJS) $(INCLUDE) -o $(NAME)

clean	:
			rm -rf $(OBJS)

fclean	:	clean
			rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all fsan clean fclean re