NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = execution/built-ins.c\
		minishell.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean : 
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(NAME)

re : clean fclean all

.PHONY : all clean fclean re