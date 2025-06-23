/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:40:59 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/23 14:12:11 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_token	*pick_d_quotes_dollar(t_lexer *lexer, t_token *token)
{
	char	*s;
	int		len;
	int		i;
	int		u;

	u = 0;
	len = 0;
	lexer->i += 2;
	i = lexer->i;
	while (lexer->line[i] && lexer->line[i++] != '"')
		len++;
	if (lexer->line[i] && lexer->line[i] && is_space(lexer->line[i]))
		token->space = 1;
	s = gc_malloc(sizeof(char) * (len + 1), getter());
	while (u < len)
	{
		s[u++] = lexer->line[lexer->i++];
	}
	s[u] = '\0';
	lexer->i += 1;
	return (set_token(token, s, T_WORD));
}

static t_token	*pick_s_quotes_dollar(t_lexer *lexer, t_token *token)
{
	char	*s;
	int		len;
	int		i;
	int		u;

	u = 0;
	len = 0;
	lexer->i += 2;
	i = lexer->i;
	while (lexer->line[i] && lexer->line[i++] != '\'')
		len++;
	if (lexer->line[i] && lexer->line[i] && is_space(lexer->line[i]))
		token->space = 1;
	s = gc_malloc(sizeof(char) * (len + 1), getter());
	while (u < len)
	{
		s[u++] = lexer->line[lexer->i++];
	}
	s[u] = '\0';
	lexer->i += 1;
	return (set_token(token, s, T_WORD));
}

static t_token	*handel_expand(t_lexer *lexer, t_token *token)
{
	int		i;
	int		len;
	char	*s;

	len = 0;
	i = lexer->i;
	while (lexer->line[i] && !is_special(lexer->line[i]))
	{
		len++;
		i++;
	}
	if (lexer->line[i])
	{
		if (lexer->line[i] && is_space(lexer->line[i]))
			token->space = 1;
	}
	s = gc_malloc(sizeof(char) * (len + 1), getter());
	ft_strlcpy(s, &lexer->line[lexer->i], len + 1);
	lexer->i = i;
	return (set_token(token, s, T_EXP));
}

t_token	*handel_dollar(t_lexer *lexer)
{
	t_token	*token;

	token = gc_malloc(sizeof(t_token), getter());
	token->d_quotes = 0;
	token->space = 0;
	if (lexer->line[lexer->i + 1] == '\0')
		return (lexer->i++, set_token(token, "$", T_WORD));
	else if (isalpha(lexer->line[lexer->i + 1]) || lexer->line[lexer->i
			+ 1] == '_' || lexer->line[lexer->i + 1] == '?')
		return (handel_expand(lexer, token));
	else if (lexer->line[lexer->i + 1] == '"')
		return (pick_d_quotes_dollar(lexer, token));
	else if (lexer->line[lexer->i + 1] == '\'')
		return (pick_s_quotes_dollar(lexer, token));
	else if (lexer->line[lexer->i + 1] == '$')
		return (lexer->i += 2, NULL);
	else if (isdigit(lexer->line[lexer->i + 1]))
		return (lexer->i += 2, NULL);
	else
		return (handel_else(lexer));
	return (NULL);
}
