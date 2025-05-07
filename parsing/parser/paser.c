/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:47:30 by nel-khad          #+#    #+#             */
/*   Updated: 2025/05/07 22:35:53 by nel-khad         ###   ########.fr       */
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
        if (token->type == T_PIPE && token->next->type == T_PIPE)
            return(EXIT_FAILURE);
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

t_token *fill_arg(t_token *token, t_command *comd, int count)
{
    int i;

    i = 0;
    while(i < count)
    {
        if(token->type == T_WORD || token->type == T_D_COTS
           || token->type == T_EXP || token->type == T_S_COTS)
        {
            comd->arg[i] = token->value;
            i++;
        }
        else if (token->type == T_RED_OUT || token->type == T_RED_IN 
            || token->type == T_RED_OUT_APEND || token->type == T_HERDOC)
        {
            comd->redir = 
        }
    }
}

t_command *get_command(t_token **token)
{
    t_command *comd;
    int count;
    t_token *cur;
    int i;

    i = 0;
    count = 0;
    cur = (*token);
    comd = gc_malloc(sizeof(t_command), getter());
    while(cur->type != T_PIPE)
    {
        count++;
        cur = cur->next;
    }
    comd->arg = gc_malloc(sizeof(char *) * (count + 1), getter());
    token = fill_arg(*token, comd, count);
    while(i < count)
    {
        if((* token)->)
        comd->arg[i] = (* token)->value;
        (* token) = (* token)->next;
        i++;
    }
    
}

t_command *creat_comand_list(t_lexer *lexer)
{
    t_command *comd;
    t_token *token;

    token = lexer->head;
    while(token && token->type != T_PIPE)
    {
       add_command(get_command(&token));
       token = token->next;
    }
}

t_command *parser(t_lexer *lexer)
{
    if(parser_check(lexer->head))
        return(parser_error());
    return(creat_comand_list(lexer->head));
}