/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:24:16 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/17 14:19:14 by zait-err         ###   ########.fr       */
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
    if(ft_strcmp(cmd->arg[0], ".") == 0)
    {
        return (cmd->arg[0]);
    }
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
    }
}

void execute_externals(t_command *cmd, t_env *env)
{
    char **envp;
    int f;
    char *pathcmd;
    pid_t pid;
    // int status;
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    pid = fork();
    if(pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if ((!cmd || !cmd->arg || !cmd->arg[0]) && cmd->redir)
        {
            open_file(cmd);
            return ; // or return NULL or handle properly
        }
        envp = get_envp(env);
        f = open_file(cmd);
        if(f == -1)
            return;
        pathcmd = search_cmd(cmd, env);
        if(ft_strcmp(pathcmd, ".") == 0)
        {
            printf(".: filename argument required\n");
            printf(".: usage: . filename [arguments]\n");
            g_exit_status = 2;
            exit(g_exit_status);
        }
        if(!pathcmd)
        {
            printf("minishell: %s No such file or directory\n", cmd->arg[0]);
            g_exit_status = 127;
            exit(g_exit_status);
        }    
        execve(pathcmd, cmd->arg, envp); //get envp from linked list t_env*;
        perror("minishell");
        exit(EXIT_FAILURE);
    }
    int status;
    waitpid(pid, &status, 0);

    if (WIFSIGNALED(status))
    {
        int sig = WTERMSIG(status);
        if (sig == SIGINT)
            write(1, "\n", 1);
        else if (sig == SIGQUIT)
            write(1, "Quit (core dumped)\n", 20);
        g_exit_status = 128 + sig;
    }
    else
        g_exit_status = WEXITSTATUS(status);
    // wait(NULL);
    // int status;
    // waitpid(pid, &status, 0);
    // if (WIFSIGNALED(status))
    //     g_exit_status = 128 + WTERMSIG(status); // like bash: 130 for SIGINT, 131 for SIGQUIT
    // else
    //     g_exit_status = WEXITSTATUS(status);
    // waitpid(pid, &status, 0);
    // exit(WEXITSTATUS(status));
}
