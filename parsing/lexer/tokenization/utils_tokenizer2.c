/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:40:59 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/23 14:24:06 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_special(char c)
{
	if (c == ' ' || c == '\t' || c == '\'' || c == '"' || c == '|' || c == '>'
		|| c == '<' || c == '\0')
		return (1);
	return (0);
}

t_token	*get_next_token(t_lexer *lexer)
{
	while (lexer->i < lexer->line_size && lexer->line[lexer->i])
	{
		if (lexer->i == lexer->line_size)
			return (NULL);
		lexer_skip_white(lexer);
		if (lexer->line[lexer->i] == '|')
			return (handel_pipe(lexer));
		else if (lexer->line[lexer->i] == '>' || lexer->line[lexer->i] == '<')
			return (handel_redir(lexer));
		else
			return (handel_word(lexer));
	}
	return (NULL);
}

void	*adding_token(t_lexer *lexer, t_token *token)
{
	if (!token)
		return (NULL);
	ft_lstadd_back(&lexer->head, token);
	return (NULL);
}

t_token	*skip_tokens(t_token *token)
{
	while (token && !token->space)
	{
		token = token->next;
	}
	return (token);
}
