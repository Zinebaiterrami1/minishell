/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:07:42 by zait-err          #+#    #+#             */
/*   Updated: 2025/05/16 20:32:53 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/mini.h"

void ft_echo(t_command *cmd)
{
    int i;
    t_command *tmp;

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
                    printf("%s\n", tmp->redir->name);
                if(tmp->arg[i])
                    write(1, tmp->arg[i], ft_strlen(tmp->arg[i]));
                if(tmp->next_com != NULL)
                    write(1, " ", 1);
                i++;
                tmp = tmp->next_com;
            }
            write(1, "\n", 1);
        }
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