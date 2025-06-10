/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:23:55 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/10 09:23:46 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Here’s the mental map:

fd 0 → Standard Input → read

fd 1 → Standard Output → write

So when you create a pipe:

pipefd[0] behaves like stdin (used to read).

pipefd[1] behaves like stdout (used to write).

That’s why when you do something like:

c
Copy
Edit
dup2(pipefd[0], STDIN_FILENO);  // read from the pipe
dup2(pipefd[1], STDOUT_FILENO); // write into the pipe
*/

pid_t global_pipes(t_command *cmd, char **envp, int curr_cmd, t_pipes *p)
{
    int error;

    error = 1;
    p->pid = fork();
   if(p->pid == -1)
   {
    perror("fork failed\n");
    return (-1);
   }     
   if(p->pid == 0)
   {
        if(curr_cmd == 0)
            error = first_command(cmd, envp, *p);
        if(curr_cmd == p->nb_cmd - 1)
            error = last_command(cmd, envp, *p);
        else 
            error = mid_command(cmd, envp, *p);
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
    p.nb_cmd = ft_lstsizee(list);
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
    return ("success\n");
}
