/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:47:30 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/29 04:45:12 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser_check(t_token *token)
{
	if (token && token->type == T_PIPE)
		return (EXIT_FAILURE);
	while (token)
	{
		if (token->type == T_PIPE && (token->next == NULL
				|| token->next->type == T_PIPE || *(token->next->value) == '('
				|| *(token->next->value) == ')'))
			return (EXIT_FAILURE);
		token = token->next;
	}
	return (EXIT_SUCCESS);
}

static void	end_of_command(t_command **cur_comd, int *f)
{
	if (*cur_comd)
		(*cur_comd)->arg[*f] = NULL;
	*cur_comd = NULL;
	*f = 0;
}

t_command	*init_comd(t_command *cur_comd, t_command **list, t_token *token)
{
	if (!cur_comd)
		return (new_comd(list, token));
	return (cur_comd);
}

t_command	*creat_comand_list(t_token *token, t_lexer *lexer)
{
	t_command	*list;
	t_command	*cur_comd;
	int			f;

	f = 0;
	list = NULL;
	cur_comd = NULL;
	while (token)
	{
		cur_comd = init_comd(cur_comd, &list, token);
		if (is_word(token->type))
			fill_arg(cur_comd, f++, token);
		else if (is_red(token->type))
			if (!handle_redirection(cur_comd, &token, lexer))
				return (NULL);
		if ((!token->next || token->type == T_PIPE) && cur_comd->arg)
			end_of_command(&cur_comd, &f);
		token = token->next;
	}
	if (lexer->error)
		return (NULL);
	return (list);
}
