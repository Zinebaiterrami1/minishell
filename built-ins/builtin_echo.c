/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:07:42 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/17 01:16:00 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void ft_echo(t_command *cmd)
// {
//     int i;
//     t_command *tmp;
//     int fd;

//     fd = 1;
//     i = 1;
//     tmp = cmd;
//     if(tmp && ft_strncmp("-n", tmp->arg[i], ft_strlen("-n")) == 0)
//     {
//         i++;
//         if(tmp && tmp->redir && tmp->redir->name)    
//             open_file(tmp);
//         while(tmp)
//         {
//             write(fd, tmp->arg[i], ft_strlen(tmp->arg[i]));
//             if(tmp->arg[i] != NULL)
//                 write(fd, " ", 1);
//             i++;
//         }
//     }
//     else
//     {   
//         if(tmp && tmp->redir && tmp->redir->name)    
//             open_file(tmp);
//         while(tmp->arg[i])
//         {   
//             write(fd, tmp->arg[i], ft_strlen(tmp->arg[i]));
//             if(tmp->arg[i] != NULL)
//                 write(fd, " ", 1);
//             i++;
//         }
//         write(1, "\n", 1);
//     }
// }

void ft_echo(t_command *cmd)
{
    int i;
    int flag;
    int fd;
    int j;
    
    i = 1;
    flag = 1;
    fd = 1;
    // if(cmd->arg[i] && ft_strcmp(cmd->arg[i], "-n") == 0)
    // {
    //     flag = 0;
    //     i++;
    // }
    if(cmd->arg[i] && cmd->arg[i][0] == '-' && cmd->arg[i][1] == 'n')
    {
        j = 2;
        while(cmd->arg[i][j] == 'n')
            j++;
        if(cmd->arg[i][j] == '\0')
        {
            flag = 0;
            i++;
        }
    }
    if(cmd && cmd->redir)
    {
        if(open_file(cmd) == -1)
        {
            g_exit_status = 1;
            return ;
        }
    }
    while(cmd->arg[i])
    {
        write(fd, cmd->arg[i], ft_strlen(cmd->arg[i]));
        if(cmd->arg[i + 1])
            write(1, " ", 1);
        i++;
    }
    if(flag == 1)
        write(1, "\n", 1);
    g_exit_status = 0;
}

/*
1. write(1, &cmd->args[i], 1); is wrong
cmd->args[i] is a char * (a string).

&cmd->args[i] is a pointer to that string → char **

write() expects a pointer to characters (char *), not a pointer to a pointer.

✅ Fix: Use write(1, cmd->args[i], ft_strlen(cmd->args[i])) to print the whole string.
*/



