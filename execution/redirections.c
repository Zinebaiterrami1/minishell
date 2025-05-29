/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:16:07 by zait-err          #+#    #+#             */
/*   Updated: 2025/05/29 23:46:41 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int open_file(t_command *cmd)
{
    //fct that open file based on the type of redirections
    t_redir *r;
    
    r = cmd->redir;
    while(r)
    {
        if(r->name)
        {
            if(r->type == T_RED_IN) // if type here is redir in > 
            {
                r->fd_in = open(r->name, O_RDONLY, 0644);
                dup2(r->fd_in, 0);
                close(r->fd_in);
            }
            else if(r->type == T_RED_OUT)
            {
                r->fd_out = open(r->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                dup2(r->fd_out, 1);
                close(r->fd_out);
            }
            else if(r->type == T_RED_OUT_APEND)
            {
                r->fd_out = open(r->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
                dup2(r->fd_out, 1);
                close(r->fd_out);
            }
            if(r->fd_out == -1 || r->fd_in == -1)
            {
                printf("error in fd\n");
                perror(r->name);
                return (-1);
            }    
        }
        r = r->next;
    }
    return (0);
}


