/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:35:56 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/30 11:41:27 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	has_space(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i++])
	{
		if (s[i] == ' ' || s[i] == '\t')
			return (1);
	}
	return (0);
}

static int	num_of_word(char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (is_space(*str))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

int	exp_helper(char *val, t_lexer *lexer, t_token *token)
{
	t_token	*last;

	last = ft_lstlast(lexer->reel_head);
	if (val && num_of_word(val) > 1 && last && is_red(last->type))
	{
		lexer->error = 1;
		g_exit_status = 1;
		return (ft_putstr_fd("ambiguous redirect\n", 2), 1);
	}
	if (val && has_space(val) && !token->d_quotes)
		split_value(val, lexer, token);
	else
		append_token(token, val, lexer, 0);
	return (0);
}

void	*creat_new_token_exp(t_lexer *lexer, t_token *token, t_env **env)
{
	char	*s;
	char	*val;

	s = NULL;
	if (!token->value)
		return (NULL);
	while (token && *token->value)
	{
		if (*token->value && !ft_strncmp((const char *)(token->value), "$", 1))
		{
			val = ft_strjoin(s, is_exp(&token->value, env));
			if (exp_helper(val, lexer, token))
				return (NULL);
		}
		else
		{
			s = ft_strjoin(s, create_string(*token->value));
			token->value++;
		}
	}
	return (lexer);
}
