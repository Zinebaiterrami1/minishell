/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:24:16 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/14 18:46:45 by zait-err         ###   ########.fr       */
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
char* search_cmd(t_command *cmd, t_env *lst)
{
    // t_command *tmp;
    char *join;
    char *joinpath;
    int i;
    char **sp;
    
    i = 0;
    // /command
    if(ft_strchr(cmd->arg[0], '/'))
    {
        if(access(cmd->arg[0], F_OK | X_OK) == 0)
            return (cmd->arg[0]);
        return (NULL);
    }
    sp = split_path(lst);
    join = ft_strjoin("/", cmd->arg[0]); // /cat
    while(sp[i])
    {
        joinpath =  ft_strjoin(sp[i], join); // path/cmd;
        if(access(joinpath, F_OK | X_OK) == 0)
            return(joinpath);
        i++;        
    }
    return (NULL);
}

char** get_envp(t_env *lst)
{
    int i;
    char **envp;
    int size;

    size = ft_lstsize(lst);
    envp = malloc(sizeof(char *) * (size + 1));
    if(!envp)
        return (NULL);
    i = 0;
    while(lst)
    {
        envp[i] = lst->line;
        i++;
        lst = lst->next;
    }
    envp[i] = NULL;
    return (envp);
}
void signal_handler_child(int signal_num)
{
    if(signal_num == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else
    {
        printf("Quit (core dumped)\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void execute_externals(t_command *cmd, t_env *env)
{
    char **envp;
    int f;
    char *pathcmd;
    pid_t pid;
    // int status;
    pid = fork();
    if(pid == 0)
    {
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
        
        envp = get_envp(env);
        f = open_file(cmd);
        if(f == -1)
            return;
        pathcmd = search_cmd(cmd, env);
        if(!pathcmd)
        {
            printf("minishell: %s command not found\n", cmd->arg[0]);
            g_exit_status = 127;
        }
        execve(pathcmd, cmd->arg, envp); //get envp from linked list t_env*;
        perror("minishell");
        exit(EXIT_FAILURE);
    }
    signal(SIGINT, signal_handler_child);
    signal(SIGQUIT, signal_handler_child);
    wait(NULL);
    // waitpid(pid, &status, 0);
    // exit(WEXITSTATUS(status));
}
