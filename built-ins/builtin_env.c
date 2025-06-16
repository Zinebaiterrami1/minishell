/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:14 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/16 13:34:18 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Initialize environment variables from system env */
t_env *init_env(char **envp)
{
    int i;
    t_env *head;
    t_env *tmp;

    head = NULL;
    tmp = NULL;
    i = 0;
    while(envp[i])
    {
        t_env *new_node = malloc(sizeof(t_env));
        new_node->line = envp[i];
        new_node->env_key = NULL;
        new_node->env_value = NULL;
        new_node->next = NULL;
        if(!head)
            head = new_node;
        else
            tmp->next = new_node;
        tmp = new_node;
        i++;
    }
    return (head);
}


// static void ft_exec_command(t_command *cmd)
// {
//     while(cmd)
//     {
//         if(ft_strncmp(cmd->arg[0], "echo", ft_strlen("echo")) == 0)
//             ft_echo(cmd);
//         else
//             printf("Error: command not found %s\n", cmd->arg[0]);
//         cmd = cmd->next_com;
//     }
// }

// /* Print all environment variables (env builtin) */
void print_env(char **envp, char **args, int argc)
{
    (void)argc;    
    (void)args;    
    // t_env *cmd;
    // t_env *tmp;
    // t_env *tmp2;
    // cmd = init_env(envp);
    // tmp = cmd;
    // tmp2 = cmd;

    // t_command *head;
    // t_command *cur;
    
    // cur = malloc(sizeof(t_command));
    // head = cur;
    // cur->arg = malloc(sizeof(char *) * 3);
    // cur->arg[0] = "echo";
    // // cur->arg[1] = "-n";
    // cur->arg[1] = "hi";
    // cur->arg[2] = NULL;
    // cur->next_com = malloc(sizeof(t_command));
    // cur->next_com->arg = malloc(sizeof(char *)*3);
    // cur->next_com->arg[0] = "echo";
    // cur->next_com->arg[1] = "hello";
    // cur->next_com->arg[2] = NULL;
    // cur->next_com->redir = malloc(sizeof(t_redir));
    // cur->next_com->redir->name = "file";
    // cur->next_com->redir->type = T_RED_OUT_APEND;
    // cur->next_com->next_com = NULL;
    // //

    // ft_exec_command(cur);
    // t_env *sp_env;
    // t_env *tmp1;

    // sp_env = split_env(tmp);
    // tmp1 = sp_env;

    // char *path;
    // path = get_env_value(tmp, "PWD");
    

    // char *key;
    // key = get_env_key(tmp2, "unix:///run/user/102723/docker.sock");
    // if(!tmp)
    // {
    //     printf("Failed to initialize environment\n");
    //     return ;
    // }
    // /*---get the value of a key giving in params---*/
    // // printf("PATH: %s\n", path);
    // // printf("KEY: %s\n", key);
    // /*---init env---*/
    // while(tmp)
    // {
    //     printf("%s\n", tmp->line);
    //     tmp = tmp->next;
    // }
    printf("-------------------------------------------\n");
    t_env *my_env = init_env(envp);
    my_env = split_env(my_env);
    // t_env *current = my_env;
    printf("Before update:\n");
    while(my_env)
    {
        printf("key : %s ------- path : %s ---------- line : %s\n", my_env->env_key, my_env->env_value, my_env->line);
        my_env = my_env->next;
    }
    // printf("after update:\n");
    // set_env_value(&current, "USER", "zait-err");
    // set_env_value(&current, "NEW_VAR", "hello_world");
    // printf("current result:\n");
    // while(current)
    // {
    //     printf("key : %s ------- path : %s\n", current->env_key, current->env_value);
    //     current = current->next;
    // }
    /*---split the env variables key=value---*/
    // while(tmp1)
    // {
    //     printf("key : %s ------- path : %s\n", tmp1->env_key, tmp1->env_value);
    //     tmp1 = tmp1->next;
    // }
    /*cd*/
    // t_env *mmy_env = init_env(envp);

    // if (argc == 1)
    //     ft_cd(NULL, &mmy_env); // No args → go to HOME
    // else
    //     ft_cd(&args[1], &mmy_env); // Use argv[1] as target directory
    // printf("Now in: %s\n", get_env_value(mmy_env, "PWD"));
    // // Show updated PWD and OLDPWD
    // t_env *tmpp = mmy_env;
    // while (tmpp) {
    //     if (strcmp(tmpp->env_key, "PWD") == 0 || strcmp(tmpp->env_key, "OLDPWD") == 0)
    //         printf("%s = %s\n", tmpp->env_key, tmpp->env_value);
    //     tmpp = tmpp->next;
    // }
    // ft_exit(args);
}

t_env *split_env(t_env *lst)
{
    t_env *tmp;
    char *equal_env;
    int key_len;

    tmp = lst;

    while(tmp)
    {
        equal_env = ft_strchr(tmp->line, '=');
        key_len = equal_env - tmp->line;
        tmp->env_key = ft_substr(tmp->line, 0, key_len);
        tmp->env_value = ft_strdup(equal_env + 1);
        tmp = tmp->next;
    }
    return (lst);
}

// static void update_line(t_env *node)
// {
//     char *tmp;
    
//     if (!node || !node->env_key)
//     return;
    
//     free(node->line); // free old line if it exists

//     if (node->env_value)
//     {
//          tmp = ft_strjoin(node->env_key, "=");
//         node->line = ft_strjoin(tmp, node->env_value);
//          free(tmp);
//     }
//     else
//     {
//          node->line = ft_strdup(node->env_key); // no '=' if value is NULL
//     }
// }

static void update_line(t_env *node)
{
    char *tmp;
    char *newline;

    if(!node || !node->env_key)
        return ;
    if(node->env_value)
    {
        tmp = ft_strjoin(node->env_key, "=");
        if(!tmp)
            return ;
        newline = ft_strjoin(tmp, node->env_value);
        if(!newline)
            return ;
    }
    else
    {
        newline = ft_strdup(node->env_key);
        if(!newline)
            return ;
    }
    // free(node->line);
    node->line = newline;
}


/* Update existing or add new environment variable */
void set_env_value(t_env **env_list, char *key, char *value)
{
    t_env *tmp;
    t_env *new_node;
    char *new_value;
    
    if(!*env_list || !env_list)
        return;
    tmp = *env_list;
    while(tmp)
    {   
        if(ft_strcmp(tmp->env_key, key) == 0)
        {
            if(value)
            {
                new_value = ft_strdup(value);
                if(!new_value)
                    return;
                // free(tmp->env_value);
                tmp->env_value = new_value;
                printf("%s\n", tmp->env_value);
            }   
            update_line(tmp);
            return ;
        }
        tmp = tmp->next;
    }
    printf("here to add new node to the list\n");
    new_node = ft_lstnew(key, value);
    if(!new_node)
        return ;
    update_line(new_node);
    ft_lstadd_backk(env_list, new_node);
    printf("node added\n");
    // free(new_value);
}

void split_and_set(char *arg, t_env **splited_env_list)
{
    char *equal_env;
    int key_len;
    char *key;
    char *value;

    equal_env = ft_strchr(arg, '=');
    if(!equal_env)
        return ;
    key_len = equal_env - arg;
    key = ft_substr(arg, 0, key_len);
    value = ft_strdup(equal_env + 1);
    if(!value)
        set_env_value(splited_env_list, key, NULL);
    else
        set_env_value(splited_env_list, key, value);
    free(key);
    free(value);
}

/* Get the value of a specific environment variable */
char *get_env_value(t_env *env_list, const char *key)
{
    t_env *tmp;

    tmp = env_list;
    // ft_display_env(env_list, NULL);
    while(tmp)
    {
        if(ft_strcmp(tmp->env_key, key) == 0)
            return (tmp->env_value);
        tmp = tmp->next;
    }
    printf("salma %s\n", key);
    return (NULL);
}

char *get_env_key(t_env *env_lst, const char *value)
{
    t_env *tmp;
    char *key;
    
    tmp = env_lst;
    while(tmp)
    {
        if(ft_strncmp(tmp->env_value, value, ft_strlen(tmp->env_value)) == 0)
        {
            key = tmp->env_key;
        }
        tmp = tmp->next;
    }
    return (key);
}

// // /* Update existing or add new environment variable */
// void set_env_value(t_env **env_list, const char *key, const char *value)
// {
//     t_env *tmp;
//     t_env *new_node;
    
//     tmp = *env_list;
//     if(!*env_list || !env_list || !tmp)
//         return;
//     printf("check if the list itself is empty===> key: %s, value: %s\n", (*env_list)->env_key, (*env_list)->env_value);
//     printf("key: %s\n, value: %s\n", tmp->env_key, tmp->env_value);
//     while(tmp)
//     {   
//         if(ft_strcmp(tmp->env_key, key) == 0)
//         {
//             printf("ana wst loop\n");
//             free(tmp->env_value);
//             tmp->env_value = ft_strdup(value);
//             printf("new value of env: %s\n", tmp->env_value);
//             return ;
//         }
//         // if(!tmp->next)
//         //     break;
//         tmp = tmp->next;
//     }
//     new_node = malloc(sizeof(t_env));
//     if(!new_node)
//         return ;
//     new_node->env_key = ft_strdup(key);
//     new_node->env_value = ft_strdup(value);
//     new_node->next = NULL;
//     ft_lstadd_backk(&tmp, new_node);
// }

void ft_display_env(t_env *env, t_command *cmd)
{
    // t_command *tmp;
    int fd;
    
    fd = 1;
    // tmp = cmd;
    // if(tmp && tmp->redir && tmp->redir->name)
    // {
    //     if(tmp->redir->type == T_RED_OUT) // >
    //         fd = open(tmp->redir->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    //     else if(tmp->redir->type == T_RED_OUT_APEND) // >>
    //         fd = open(tmp->redir->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
    //     if(fd < 0)
    //         printf("error fd\n");
    // }
    if(cmd && cmd->redir && cmd->redir->name)
    {
        if(open_file(cmd) == -1)
        {
            g_exit_status = 1;
            return ;
        }
    }
    if(!env)
    {
        g_exit_status = 1;
        return ;
    }
    while(env)
    {
        if(env->env_value)
        {
            write(fd, env->env_key, ft_strlen(env->env_key));
            write(fd, "=\"", 2);
            write(fd,  env->env_value, ft_strlen( env->env_value));
            write(fd, "\"", 1);
            write(fd, "\n", 1);
            // printf("%s=\"%s\"\n", env->env_key, env->env_value);
        }
        env = env->next;
    }
    g_exit_status = 0;
}