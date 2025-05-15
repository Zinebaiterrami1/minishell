/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:36 by zait-err          #+#    #+#             */
/*   Updated: 2025/05/15 21:08:38 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/mini.h"

void ft_pwd()
{
    char buffer[BUFFER_SIZE];
    if(getcwd(buffer, BUFFER_SIZE) == NULL)
        write(2, "Cannot get the current directory ... !\n", ft_strlen("Cannot get the current directory ... !\n"));
    else
        write(1, buffer, ft_strlen(buffer));
    write(1, "\n", 1);
}