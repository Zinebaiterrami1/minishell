/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:20:10 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/28 14:11:34 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*parser(t_lexer *lexer)
{
	if (parser_check(lexer->head))
		return (syntax_error(1));
	return (creat_comand_list(lexer->reel_head, lexer));
}
