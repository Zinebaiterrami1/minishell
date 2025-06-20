CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined -g3
SRC = built-ins/builtin_echo.c minishell.c built-ins/builtin_pwd.c built-ins/builtin_env.c built-ins/builtin_cd.c built-ins/builtin_exit.c parsing/lexer/lexer.c parsing/parser/parser.c parsing/garbage_collector/gc.c parsing/garbage_collector/gc_utils.c\
		parsing/lexer/utils.c built-ins/builtin_export.c built-ins/builtin_unset.c built-ins/builtin_env1.c built-ins/builtin_export1.c\
		execution/redirections.c execution/path.c execution/multi_pipes.c execution/exec_commands.c execution/path_utils.c execution/utils.c \
		
NAME= minishell

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