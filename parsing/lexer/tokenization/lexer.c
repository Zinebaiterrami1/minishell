/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:40:59 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/29 02:47:53 by nel-khad         ###   ########.fr       */
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
		return (syntax_error("minishel: syntax error near unexpected token"));
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
	if (reel_list(lexer, env))
		return (NULL);
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
	if (is_buitins(list) && ft_lstsizee(list) == 1)
		execute_buitlins(env_lst, list);
	else if (!is_buitins(list) && ft_lstsizee(list) == 1)
		execute_externals(list, *env_lst);
	else if (ft_lstsizee(list) > 1)
		if (!multiple_pipes(env_lst, list))
			return (list);
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	close(stdin);
	close(stdout);
	return (NULL);
}
