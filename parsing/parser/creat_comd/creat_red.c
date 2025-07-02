/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:47:30 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/30 11:40:49 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	add_redir(t_redir **list, t_redir *new)
{
	t_redir	*ptr;

	if (new == NULL || !list)
		return ;
	ptr = *list;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	while (ptr->next)
	{
		ptr = ptr->next;
	}
	if (ptr)
		ptr->next = new;
	return ;
}

static int	creat_red(t_redir **red_list, int type, t_token *token
	, t_lexer *lexer)
{
	t_redir	*redir;

	redir = gc_malloc(sizeof(t_redir), getter());
	redir->name = token->value;
	redir->type = type;
	redir->next = NULL;
	redir->herdoc = NULL;
	redir->fd_in = 0;
	redir->fd_out = 1;
	if (type == T_HERDOC)
	{
		if (handel_herdoc(lexer->env, token, redir) || !redir)
			return (EXIT_FAILURE);
	}
	add_redir(red_list, redir);
	return (EXIT_SUCCESS);
}

void	*handle_redirection(t_command *cur_comd, t_token **token
	, t_lexer *lexer)
{
	int	red_type;

	red_type = (*token)->type;
	if ((*token)->next && is_word((*token)->next->type))
	{
		*token = (*token)->next;
		if (creat_red(&cur_comd->redir, red_type, *token, lexer))
			return (NULL);
	}
	else
	{
		g_exit_status = 2;
		return (syntax_error("minishel: syntax error near unexpected token"));
	}
	return (lexer);
}
