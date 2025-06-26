/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:40:59 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/26 10:08:37 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_exp(char *var, t_env **env)
{
	char	*s;

	s = get_env_value(*env, var);
	return (s);
}

void	print_list(t_token *token)
{
	printf("token list : ");
	while (token)
	{
		token = token->next;
	}
	printf("\n");
}

void	print_list2(t_token *token)
{
	printf("token list222 : ");
	while (token)
	{
		printf("%s (%d) [%d] --> ", token->value, token->type, token->space);
		token = token->next;
	}
	printf("\n");
}

t_command	*parsing(char *line, t_env **env)
{
	t_lexer	*lexer;
	t_token	*token;

	(void)env;
	if (check(line))
		return (syntax_error(0));
	lexer = init_lexer(line, env);
	while (lexer->i < lexer->line_size)
	{
		lexer_skip_white(lexer);
		if (lexer->line[lexer->i] == '\n' || lexer->line[lexer->i] == '\0')
			break ;
		token = get_next_token(lexer);
		if (token)
			adding_token(lexer, token);
		if (lexer->error)
			return (NULL);
	}
	print_list(lexer->head);
	if (reel_list(lexer, env))
		return (NULL);
	print_list2(lexer->reel_head);
	return (parser(lexer));
}

void	*minishell(char *line, t_env **env_lst)
{
	t_command	*list;

	int (stdin), (stdout);
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	list = parsing(line, env_lst);
	if (!list)
		return (NULL);
	printf("------------------------------------------\n");
	if (is_buitins(list) && ft_lstsizee(list) == 1)
		execute_buitlins(env_lst, list);
	else if (!is_buitins(list) && ft_lstsizee(list) == 1)
		execute_externals(list, *env_lst);
	else if (ft_lstsizee(list) > 1)
		if (!multiple_pipes(env_lst, list))
			return (SUCCESS_PTR);
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	close(stdin);
	close(stdout);
	return (NULL);
}

// int lexer(char *line)
// {
//     t_lexer *lexer;
//     t_token *token;

//     if(check(line))
//         return(syntax_error());
//     lexer = init_lexer(line);
//     while(lexer->i < lexer->line_size)
//     {
//         lexer_skip_white(lexer);
//         if(lexer->line[lexer->i] == '\n' || lexer->line[lexer->i] == '\0')
//             return(1);
//         token = get_next_token(lexer);
//         if(token)
//             adding_token(lexer, token);
//         if(lexer->error)
//             return(1);
//     }
//     print_list(lexer->head);
//     parser(lexer);
//     free_all(getter());
//     return(0);
// }

// int main(int argc, char **argv, char **env)
// {
//     char *line;

//     (void) argc;
//     (void) argv;
//     while(1)
//     {
//         line = readline("$minishell V2 ");
//         if (!line)
//             break ;
//         if (line[0] == '\0')
//             continue ;
//         add_history(line);
//         if(minishell(line, env))
//         {
//             free(line);
//             continue ;
//         }
//         free(line);
//         // if(lexer(line) == 1)
//         // {
//         //     free(line);
//         //     syntax_error();
//         //     continue ;
//         // }
//     }
// }
