/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:16:07 by zait-err          #+#    #+#             */
/*   Updated: 2025/05/29 21:50:26 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void open_file(t_command **args)
{
    //fct that open file based on the type of redirections
    t_command *tmp;
    
    tmp = *args;
    while(tmp)
    {
        if(tmp->redir->type == T_RED_IN) // if type here is redir in > 
        {
            tmp->redir->fd_out = open(tmp->redir->name, O_CREAT | O_WRONLY | O_TRUNC, 7777);
            dup2(tmp->redir->fd_out, 1);
            close(tmp->redir->fd_out);
        }
        else if(tmp->redir->type == T_RED_OUT)
        {
            tmp->redir->fd_in = open(tmp->redir->name, O_CREAT | O_WRONLY, 7777);
            dup2(tmp->redir->fd_in, 1);
            close(tmp->redir->fd_in);
        }
        else if(tmp->redir->type == T_RED_OUT_APEND)
        {
            tmp->redir->fd_in = open(tmp->redir->name, O_CREAT | O_WRONLY | O_APPEND, 7777);
            dup2(tmp->redir->fd_in, 1);
            close(tmp->redir->fd_in);
        }
        tmp = tmp->redir->next;
    }
}


