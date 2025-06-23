/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:40:59 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/23 14:24:38 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_token	*set_token(t_token *token, char *cmd, int type)
{
	token->type = type;
	token->value = cmd;
	token->next = NULL;
	return (token);
}

t_token	*set_new_token(t_token *token, char *s, t_token *old_token,
		int separat_red)
{
	if (s)
		token->value = s;
	else
		token->value = old_token->value;
	if (separat_red)
		token->space = 1;
	else
		token->space = old_token->space;
	if (old_token->type == T_WORD && old_token->next && !token->space
		&& !is_red(old_token->next->type) && old_token->next->type != T_PIPE)
		token->type = old_token->next->type;
	else
		token->type = old_token->type;
	token->next = NULL;
	printf("token = %s, %d\n", token->value, token->type);
	return (token);
}

void	*adding_new_token(t_lexer *lexer, t_token *token)
{
	t_token	*last;

	if (!token)
		return (NULL);
	last = ft_lstlast(lexer->reel_head);
	if (last && !last->space && is_word(token->type))
	{
		last->value = ft_strjoin(last->value, token->value);
		last->space = token->space;
		if (last->type == T_WORD)
			last->type = token->type;
	}
	else
		ft_lstadd_back(&lexer->reel_head, token);
	return (NULL);
}

void	append_token(t_token *old_token, char *s, t_lexer *lexer, int separ_red)
{
	t_token	*token;

	token = gc_malloc(sizeof(t_token), getter());
	set_new_token(token, s, old_token, separ_red);
	printf("append_token->val ____________________ %s\n", token->value);
	adding_new_token(lexer, token);
}

int	reel_list(t_lexer *lexer, t_env **env)
{
	t_token	*token;
	int		herd_num;

	herd_num = 0;
	token = lexer->head;
	while (token)
	{
		if (token->type == T_EXP)
		{
			if (!creat_new_token_exp(lexer, token, env))
				return (1);
		}
		else
			append_token(token, NULL, lexer, 0);
		if (token->type == T_HERDOC)
			herd_num++;
		token = token->next;
	}
	if (herd_num >= 16)
	{
		ft_putstr_fd("maximum here-document count exceeded\n", 2);
		return (1);
	}
	return (0);
}
