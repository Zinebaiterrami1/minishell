CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
SRC = lexer/lexer.c lexer/utils.c garbage_collector/gc.c parser/parser.c lexer/builtin_env.c

NAME = mini

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	@echo "🚀 Building the project..."
	@make -s all -C libft
	@make -s bonus -C libft
	@$(CC) $(CFLAGS) $(OBJ) libft/libft.a -lreadline -o $(NAME)
	@echo "✅ Build completed successfully!"

all : $(NAME)

fclean : clean
	@rm -rf $(NAME)
	@make -s fclean -C libft

clean :
	@echo "🧹 Cleaning up..."
	@rm -rf $(OBJ)
	@make -s clean -C libft
	@make -s clean -C libft
	@echo "🗑️  Cleanup done!"

re : fclean all

.PHONY: all clean fclean re