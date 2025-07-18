/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:35:56 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/29 02:43:12 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	helper(char **token_val, t_env **env, char **ret)
{
	char	*s;

	s = NULL;
	(*token_val)++;
	while (**token_val == '$')
		(*token_val)++;
	if (ft_isalpha(**token_val) || **token_val == '_')
	{
		while (**token_val == '_' || ft_isalnum(**token_val))
		{
			s = ft_strjoin(s, create_string(**token_val));
			(*token_val)++;
		}
		(*ret) = ft_strjoin((*ret), get_exp(s, env));
		s = NULL;
	}
	else if (**token_val == '?')
	{
		(*ret) = ft_strjoin((*ret), ft_itoa(g_exit_status));
		(*token_val)++;
	}
}

char	*is_exp(char **token_val, t_env **env) //.h
{
	char	*ret;

	ret = gc_strdup("");
	while (**token_val)
	{
		if (**token_val == '$' && *((*token_val) + 1) != '\0'
			&& !is_special(*((*token_val) + 1)) && *((*token_val) + 1) != '=')
		{
			helper(token_val, env, &ret);
		}
		else
		{
			ret = ft_strjoin(ret, create_string(**token_val));
			(*token_val)++;
		}
	}
	return (ret);
}

static int	is_export(t_token *last, char *val)
{
	int	i;

	i = 0;
	while (val[i] && val[i] != '=')
	{
		if (val[i] == ' ')
			return (0);
		i++;
	}
	if (last->value && !ft_strcmp(last->value, "export"))
		return (1);
	return (0);
}

void	split_value(char *val, t_lexer *lexer, t_token *token)
{
	char	**splited;
	int		i;

	i = 0;
	splited = ft_split(val, ' ');
	if (is_export(ft_lstlast(lexer->reel_head), val))
		append_token(token, val, lexer, 0);
	else
	{
		while (splited[i])
		{
			append_token(token, splited[i], lexer, 1);
			i++;
		}
	}
}
