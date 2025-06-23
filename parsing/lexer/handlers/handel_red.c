/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:35:56 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/23 14:15:59 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../mimi.h"
#include "../../../includes/minishell.h"

static t_token	*handel_redir_out(t_token *token, t_lexer *lexer)
{
	if (lexer->line[lexer->i + 1] == '>')
		return (lexer->i += 2, set_token(token, ">>", T_RED_OUT_APEND));
	else
		return (lexer->i += 1, set_token(token, ">", T_RED_OUT));
}

static t_token	*handel_redir_in(t_token *token, t_lexer *lexer)
{
	if (lexer->line[lexer->i + 1] == '<')
		return (lexer->i += 2, set_token(token, "<<", T_HERDOC));
	else
		return (lexer->i += 1, set_token(token, "<", T_RED_IN));
}

t_token	*handel_redir(t_lexer *lexer)
{
	t_token	*token;

	token = gc_malloc(sizeof(t_token), getter());
	token->d_quotes = 0;
	token->space = 1;
	if (lexer->line[lexer->i] == '>')
		return (handel_redir_out(token, lexer));
	else if (lexer->line[lexer->i] == '<')
		return (handel_redir_in(token, lexer));
	return (NULL);
}
