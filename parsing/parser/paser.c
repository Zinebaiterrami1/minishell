/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:47:30 by nel-khad          #+#    #+#             */
/*   Updated: 2025/04/30 20:51:47 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mimi.h"
//"$$$HOME"
int parser_check(t_token *token)
{
    if(token->value == "|")
        return(EXIT_FAILURE);
    while(token)
    {
        if(token->type == T_RED_IN || token->type == T_RED_OUT 
        || token->type == T_RED_IN || token->type == T_HERDOC)
        {
            if (token->next->type == NULL || token->next->type == T_RED_IN || token->next->type == T_RED_OUT 
            || token->next->type == T_RED_IN || token->next->type == T_HERDOC 
            || token->next->type == T_PIPE)
                return(EXIT_FAILURE);
        }
        token = token->next;
    }
    return(EXIT_SUCCESS);
}

void *parser_error()
{
    printf("syntax error\n");
    return(NULL);
}

t_command *creat_comand_list(t_lexer *lexer)
{
    t_command *comd;

    comd = malloc()
}

t_command *parser(t_lexer *lexer)
{
    if(parser_check(lexer->head))
        return(parser_error());
    return(creat_comand_list(lexer->head));
}