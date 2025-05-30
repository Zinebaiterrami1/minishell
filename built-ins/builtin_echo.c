/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:07:42 by zait-err          #+#    #+#             */
/*   Updated: 2025/05/30 14:14:41 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_command **init_cmd(char **args)
// {
//     int i;
//     t_command *head;
//     t_command *tmp;
    
//     i = 1;
//     head = NULL;
//     tmp = NULL;
//     while(args[i])
//     {
//         t_command *new_node = malloc(sizeof(t_command));
//         new_node->arg = args[i];
//         new_node->
//     }
// }

void ft_echo(t_command *cmd)
{
    int i;
    t_command *tmp;
    int fd;

    fd = 1;
    i = 1;
    tmp = cmd;

        if(tmp && ft_strncmp("-n", tmp->arg[i], ft_strlen("-n")) == 0)
        {
            i++;
            while(tmp)
            {
                if(tmp->arg[i])
                    write(1, tmp->arg[i], ft_strlen(tmp->arg[i]));
                if(tmp->next_com != NULL)
                    write(1, " ", 1);
                i++;
                tmp = tmp->next_com;
            }
        }
        else
        {
            while(tmp)
            {   
                if(tmp && tmp->redir && tmp->redir->name)    
                {
                    open_file(tmp);
                }
                if(tmp->arg[i])
                    write(1, tmp->arg[i], ft_strlen(tmp->arg[i]));
                if(tmp->next_com != NULL)
                    write(1, " ", 1);
                i++;
                tmp = tmp->next_com;
            }
            write(1, "\n", 1);
        }
        //Handle redirection if present
        if(tmp && tmp->redir && tmp->redir->name)
        {
            if(tmp->redir->type == T_RED_OUT) // >
                fd = open(tmp->redir->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            else if(tmp->redir->type == T_RED_OUT_APEND) // >>
                fd = open(tmp->redir->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
            if(fd < 0)
                printf("error fd\n");
        }
        while(tmp && tmp->arg[i])
        {
            write(fd, tmp->arg[i], ft_strlen(tmp->arg[i]));
            if(tmp->arg[i + 1])
                write(fd, " ", 1);
            i++;
        }
        if(fd != 1)
            close(fd);
}

// void ft_echo_in_file(int fd)
// {

// }


/*
1. write(1, &cmd->args[i], 1); is wrong
cmd->args[i] is a char * (a string).

&cmd->args[i] is a pointer to that string → char **

write() expects a pointer to characters (char *), not a pointer to a pointer.

✅ Fix: Use write(1, cmd->args[i], ft_strlen(cmd->args[i])) to print the whole string.
*/