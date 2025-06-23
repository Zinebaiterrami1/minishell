/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:35:56 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/23 14:17:14 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../mimi.h"
#include "../../../includes/minishell.h"

static t_token	*dilim_helper(void)
{
	t_token	*token;

	token = gc_malloc(sizeof(t_token), getter());
	token->d_quotes = 0;
	token->space = 0;
	token->type = T_WORD;
	return (token);
}

static int	is_char_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

t_token	*handel_dilim(t_lexer *lexer)
{
	t_token	*token;
	char	*s;
	int		i;

	i = lexer->i;
	s = gc_strdup("");
	token = dilim_helper();
	while (lexer->line[i] && !is_space(lexer->line[i])
		&& !is_char_redir(lexer->line[i]))
	{
		if (lexer->line[i] == '"' || lexer->line[i] == '\'')
		{
			token->type = T_S_COTS;
			token->d_quotes = 1;
		}
		else
			s = ft_strjoin(s, create_string(lexer->line[i]));
		i++;
	}
	if (lexer->line[i] && is_space(lexer->line[i]))
		token->space = 1;
	lexer->i = i;
	return (set_token(token, s, token->type));
}

t_token	*handel_pipe(t_lexer *lexer)
{
	t_token	*token;

	token = gc_malloc(sizeof(t_token), getter());
	token->d_quotes = 0;
	token->space = 1;
	lexer->i++;
	return (set_token(token, "|", T_PIPE));
}
