CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
SRC = lexer/lexer.c lexer/utils.c garbage_collector/gc.c parser/parser.c 

NAME = mini

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	@echo "🚀 Building the project..."
	@make -s all -C libft_nouss
	@make -s bonus -C libft_nouss
	@$(CC) $(CFLAGS) $(OBJ) libft_nouss/libft.a -lreadline -o $(NAME)
	@echo "✅ Build completed successfully!"

all : $(NAME)

fclean : clean
	@rm -rf $(NAME)
	@make -s fclean -C libft_nouss

clean :
	@echo "🧹 Cleaning up..."
	@rm -rf $(OBJ)
	@make -s clean -C libft_nouss
	@make -s clean -C libft_nouss
	@echo "🗑️  Cleanup done!"

re : fclean all

.PHONY: all clean fclean re