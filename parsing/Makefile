CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
SRC = main.c

NAME= mini

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	@echo "🚀 Building the project..."
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "✅ Build completed successfully!"

all : $(NAME)

fclean : clean
	@rm -rf $(NAME)

clean :
	@echo "🧹 Cleaning up..."
	@rm -rf $(OBJ)
	@echo "🗑️  Cleanup done!"

re : fclean all

.PHONY: all clean fclean re