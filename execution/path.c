/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:24:16 by zait-err          #+#    #+#             */
/*   Updated: 2025/05/28 22:24:16 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//fct get path
char* ft_getpath(t_env *lst)
{
    t_env *tmp;
    
    tmp = lst;
    while(tmp)
    {
        if(ft_strcmp(tmp->env_key, "PATH") == 0)
        {
            return(tmp->env_value);
        }
        tmp = tmp->next;
    }
    return (NULL);
}

//fct split
char** split_path(t_env *lst)
{
    char *path;
    char **sp;
    
    path = ft_getpath(lst);
    sp = ft_split(path, ':');
    return (sp);
}

//search the command in each path to find it and pass it to access
char* search_cmd(t_command *cmd, char **sp)
{
    t_command *tmp;
    char *join;
    char *joinpath;
    int i;
    
    i = 0;
    // /command
    join = ft_strjoin("/", cmd->arg[0]); // /cat
    while(sp[i])
    {
        joinpath =  ft_strjoin(sp[i], join); // path/cmd;
        if(access(joinpath, F_OK | X_OK))
            return(joinpath);
        i++;        
    }
    return (NULL);
}

int ft_dup(char *pathcmd, t_command *cmd)
{
    dup2(cmd->fd_out, 1);
    dup2(cmd->fd_in, 0);
    close(cmd->fd_in); //check if fd == 0, if yes no close else close
    close(cmd->fd_out);
    // execve(pathcmd, cmd->arg, envp); //get envp from linked list t_env*;
}