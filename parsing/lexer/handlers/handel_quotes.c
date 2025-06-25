/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:35:56 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/24 18:12:23 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../mimi.h"
#include "../../../includes/minishell.h"

char	*get_string(char *s, int i)
{
	int		j;
	char	*str;

	j = 0;
	str = NULL;
	while (j < i)
	{
		if (s[j] == '$' && s[j + 1] && s[j + 1] == '$')
			j += 2;
		if (j < i)
			str = ft_strjoin(str, create_string(s[j]));
		j++;
	}
	return (str);
}

static void	helper(int *i, char *str, int *count)
{
	while (str[*i] && str[*i] == '$')
	{
		(*count)++;
		(*i)++;
	}
}

int	has_dollar(char **s)
{
	int		i;
	int		count;
	char	*str;

	str = *s;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			helper(&i, str, &count);
		}
		if ((str[i] && (ft_isalpha(str[i]) || str[i] == '_') && count)
			|| !str[i])
		{
			*s = ft_strjoin(get_string(*s, i), &str[i]);
			return (1);
		}
		if (str[i])
			i++;
	}
	return (0);
}

t_token	*handel_s_quotes(t_lexer *lexer)
{
	t_token	*token;
	int		len;
	char	*s;
	int		i;

	i = lexer->i;
	len = 0;
	lexer->status_s = 1;
	token = gc_malloc(sizeof(t_token), getter());
	token->d_quotes = 0;
	token->space = 0;
	while (lexer->line[i + 1] && lexer->line[++i] != '\'')
		len++;
	if (lexer->line[i] && lexer->line[i + 1] && is_space(lexer->line[i + 1]))
		token->space = 1;
	s = gc_malloc(sizeof(char) * (len + 1), getter());
	ft_strlcpy(s, &lexer->line[++lexer->i], len + 1);
	lexer->i = i + 1;
	return (set_token(token, s, T_S_COTS));
}

t_token	*handel_d_quotes(t_lexer *lexer)
{
	t_token	*token;
	int		len;
	char	*s;
	int		i;

	i = lexer->i;
	len = 0;
	lexer->status_s = 1;
	token = gc_malloc(sizeof(t_token), getter());
	token->space = 0;
	token->d_quotes = 1;
	while (lexer->line[i + 1] && lexer->line[++i] != '"')
		len++;
	if (lexer->line[i] && lexer->line[i + 1] && is_space(lexer->line[i + 1]))
		token->space = 1;
	s = gc_malloc(sizeof(char) * (len + 1), getter());
	ft_strlcpy(s, &lexer->line[++lexer->i], len + 1);
	lexer->i = i + 1;
	if (has_dollar(&s))
		return (set_token(token, s, T_EXP));
	return (set_token(token, s, T_D_COTS));
}
