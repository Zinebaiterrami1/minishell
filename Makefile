CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -fsanitize=undefined -g3
SRC = built-ins/builtin_echo.c minishell.c built-ins/builtin_pwd.c built-ins/builtin_env.c built-ins/builtin_cd.c built-ins/builtin_exit.c parsing/parser/parser.c \
parsing/parser/creat_comd/creat_comd.c parsing/parser/creat_comd/creat_red.c parsing/parser/herdoc/herdoc_exp.c parsing/parser/herdoc/herdoc.c parsing/parser/herdoc/utils.c \
parsing/lexer/expander/expander.c parsing/lexer/expander/utils.c parsing/lexer/handlers/handel_exp.c parsing/lexer/handlers/handel_quotes.c parsing/lexer/handlers/handel_red.c\
parsing/lexer/handlers/handel_word.c parsing/lexer/handlers/other_handlers.c \
parsing/lexer/tokenization/lexer.c parsing/lexer/tokenization/tokenizer.c parsing/lexer/tokenization/utils_tokenizer.c parsing/lexer/tokenization/utils_tokenizer2.c \
parsing/garbage_collector/gc_utils.c parsing/garbage_collector/gc.c\
		built-ins/builtin_export.c built-ins/builtin_unset.c \
		execution/redirections.c execution/path.c execution/multi_pipes.c execution/exec_commands.c 
		
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