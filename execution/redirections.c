/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:16:07 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/18 22:23:36 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int open_file(t_command *cmd)
{
    t_redir *r;
    
    r = cmd->redir;
    while(r)
    {
        printf("open file desc\n");
        if(r->name)
        {
            if(r->type == T_RED_IN)
                r->fd_in = open(r->name, O_RDONLY);
            else if(r->type == T_HERDOC)
                r->fd_in = open(r->name, O_RDONLY);
            else if(r->type == T_RED_OUT)
                r->fd_out = open(r->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            else if(r->type == T_RED_OUT_APEND)
                r->fd_out = open(r->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
            if(r->fd_out == -1 || r->fd_in == -1)
            {
                printf("error in fd\n");
                // perror(r->name);
                return (-1);
            }
            printf("file name: %s\n", r->name);
            if(r->fd_in != 0)
                dup2(r->fd_in, 0);
            if(r->fd_out != 1)
                dup2(r->fd_out, 1);
            if(r->fd_in > 2)
                close(r->fd_in);
            if(r->fd_out > 2)
                close(r->fd_out);
        }
        r = r->next;
    }
    return (0);
}
