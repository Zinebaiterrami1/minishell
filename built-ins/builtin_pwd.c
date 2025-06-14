/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:36 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/14 23:44:46 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
 
void ft_pwd()
{
    char buffer[BUFFER_SIZE];
    if(getcwd(buffer, BUFFER_SIZE) == NULL)
    {
        write(2, "Cannot get the current directory ... !\n", ft_strlen("Cannot get the current directory ... !\n"));
        g_exit_status = 1;
    }
    else
    {
        write(1, buffer, ft_strlen(buffer));
        g_exit_status = 0;
    }    
    write(1, "\n", 1);
}