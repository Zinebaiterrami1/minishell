/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:23:55 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/05 16:02:47 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/structs.h"


pid_t global_pipes(t_command *cmd, char **envp, int curr_cmd, t_pipes *p)
{
    int error;
   p->pid = fork();
   if(p->pid == -1)
   {
    perror("fork failed\n");
    return (-1);
   }     
   if(p->pid == 0)
   {
        if(curr_cmd == 0)
            error = first_command(cmd, envp, p->fd);
        if(curr_cmd == p->nb_cmd - 1)
            error = last_command(cmd, envp, p->fd);
        else 
            error = mid_command(cmd, envp, p->fd);
   }
   if(error == -1)
    return(error);
   dup2(p->fd[0], 0);
   close(p->fd[0]);
   close(p->fd[1]);
   return (p->pid);
}

int wait_children(t_pipes *p)
{
    int status;
    int i;

    i = 0;
    status = 0;
    waitpid(p->pid, &status, 0);
    while(i < p->nb_cmd)
    {
        wait(NULL);
        i++;
    }
    return (status);
}

void *multiple_pipes(char **env, t_command *list)
{
    int curr_cmd;
    t_pipes p;
    
    curr_cmd = 0;
    p.nb_cmd = ft_lstsize(list);
    while(list && curr_cmd < p.nb_cmd)
    {
        if(pipe(p.fd) == -1)
        {
            perror("pipe failed\n");
            return (NULL);
        }
        p.pid = global_pipes(list, env, curr_cmd, &p);
        if(p.pid == -1)
            return (NULL);
        list = list->next_com;
        curr_cmd++;
    }
    // wait_children(); //return exit status li kat9adha waitpid
    // g_exit_status //w nhto f hada
    g_exit_status = wait_children(&p);
}
