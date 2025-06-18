/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:13:59 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/18 22:19:02 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int first_command(t_command *cmd, t_env **envp, t_pipes p)
{
    if(cmd->redir)
    {
        if(open_file(cmd) == -1)
            return (-1);
    }
    else
    {
        dup2(p.fd[1], STDOUT_FILENO);
        close(p.fd[0]);
        close(p.fd[1]);
    }
    execve(search_cmd(cmd, *envp), cmd->arg, get_envp(*envp));
    return (0);
}

int last_command(t_command *cmd, t_env **envp, t_pipes p)
{
    if(cmd->redir)
    {
        if(open_file(cmd) == -1)
            return (-1);
    }
    else
    {
        dup2(STDOUT_FILENO, p.fd[0]);
        close(p.fd[0]);
        close(p.fd[1]);
    }
    execve(search_cmd(cmd, *envp), cmd->arg, get_envp(*envp));    
    return (0);
}

int mid_command(t_command *cmd, t_env **envp, t_pipes p)
{
    if(cmd->redir)
    {
        if(open_file(cmd) == -1)
            return (-1);
    }
    else
    {
        dup2(p.fd[1], STDOUT_FILENO);
        close(p.fd[0]);
        close(p.fd[1]);
    }
    execve(search_cmd(cmd, *envp), cmd->arg, get_envp(*envp));
    return (0);
}