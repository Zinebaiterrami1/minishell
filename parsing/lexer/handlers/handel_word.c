/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:35:56 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/23 14:22:16 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../mimi.h"
#include "../../../includes/minishell.h"

char	*create_string(char c)
{
	char	*tmp;

	if (c == '\0')
		tmp = gc_strdup("");
	tmp = gc_malloc(sizeof(char) * 2, getter());
	tmp[0] = c;
	tmp[1] = '\0';
	return (tmp);
}

t_token	*handel_else(t_lexer *lexer)
{
	t_token	*token;
	int		len;
	char	*s;
	int		i;

	i = lexer->i;
	len = 0;
	token = gc_malloc(sizeof(t_token), getter());
	token->d_quotes = 0;
	token->space = 0;
	while (lexer->line[i] && !is_special(lexer->line[i]))
	{
		len++;
		i++;
	}
	if (lexer->line[i] && is_space(lexer->line[i]))
		token->space = 1;
	s = gc_malloc(sizeof(char) * (len + 1), getter());
	ft_strlcpy(s, &lexer->line[lexer->i], len + 1);
	lexer->i = i;
	if (has_dollar(&s))
		return (set_token(token, s, T_EXP));
	return (set_token(token, s, T_WORD));
}

t_token	*handel_word(t_lexer *lexer)
{
	t_token	*last;

	last = ft_lstlast(lexer->head);
	if (last && last->type == T_HERDOC)
		return (handel_dilim(lexer));
	if (lexer->line[lexer->i] == '\'')
		return (handel_s_quotes(lexer));
	else if (lexer->line[lexer->i] == '"')
		return (handel_d_quotes(lexer));
	else if (lexer->line[lexer->i] == '$')
		return (handel_dollar(lexer));
	else
		return (handel_else(lexer));
	return (NULL);
}
