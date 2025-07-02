/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:20:10 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/30 11:40:29 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*parser(t_lexer *lexer)
{
	if (parser_check(lexer->head))
	{
		g_exit_status = 2;
		return (syntax_error("minishel: syntax error near unexpected token"));
	}
	return (creat_comand_list(lexer->reel_head, lexer));
}
