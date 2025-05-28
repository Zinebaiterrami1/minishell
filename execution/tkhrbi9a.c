/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:38:07 by zait-err          #+#    #+#             */
/*   Updated: 2025/05/28 21:20:56 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//So in this file i will, Execute simple commands, 
//using acces to verify is it the real path that has the command executable, 
//and execve to execute it and fork;
t_env   **f_env(void)
{
    static t_env *env;
    return(&env);
}

t_env*    fill_env(char **envp)
{
    t_env *env;
    env = *f_env();

    env = init_env(envp);
    env = split_env(env);
    return (env);
}
void ft_execute_command(void)
{
    char *path;
    char **envp;
    pid_t pid;

    pid = fork();
    if(pid == 0)
    {
        
    }  
}

int main(int argc, char **args, char **env)
{

    fill_env(env);
    ft_execute_command();
}

//get path
//spliti, w nchd path
//path n3tih l access 
//if rederection, open file descriptor, diyal cmd w diyal files, 
//ila makntch red n3tiha 0 1 
//env
//execv
