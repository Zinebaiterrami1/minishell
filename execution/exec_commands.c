/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:13:59 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/11 19:56:43 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int first_command(t_command *cmd, char **envp, t_pipes p)
{
    // t_redir *r;
     
    if(cmd->redir)
    {
        // r = cmd->redir;
        if(open_file(cmd) == -1)
            return (-1);
    }
    else
    {
        dup2(p.fd[1], STDOUT_FILENO);
        close(p.fd[0]);
        close(p.fd[1]);
    }
    execve(search_cmd(cmd, split_env(init_env(envp))), cmd->arg, envp);
    return (0);
}

int last_command(t_command *cmd, char **envp, t_pipes p)
{
    // t_redir *r;
    
    if(cmd->redir)
    {
        // r = cmd->redir;
        if(open_file(cmd) == -1)
            return (-1);
    }
    else
    {
        dup2(p.fd[0], STDIN_FILENO);
        close(p.fd[0]);
        close(p.fd[1]);
    }
    execve(search_cmd(cmd, split_env(init_env(envp))), cmd->arg, envp);
    return (0);
}

int mid_command(t_command *cmd, char **envp, t_pipes p)
{
    // t_redir *r;

    if(cmd->redir)
    {
        // r = cmd->redir;
        if(open_file(cmd) == -1)
            return (-1);
    }
    else
    {
        dup2(p.fd[1], STDOUT_FILENO);
        close(p.fd[0]);
        close(p.fd[1]);
    }
    execve(search_cmd(cmd, split_env(init_env(envp))), cmd->arg, envp);
    return (0);
}