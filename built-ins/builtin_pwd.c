/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:36 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/29 05:00:47 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	display_pwd(t_command *cmd)
{
	ft_putstr_fd("bash: pwd: ", 1);
	ft_putstr_fd(cmd->arg[1], 1);
	ft_putstr_fd(": invalid option\n", 1);
}

void	ft_pwd(t_command *cmd)
{
	char	buffer[BUFFER_SIZE];

	if (getcwd(buffer, BUFFER_SIZE) == NULL)
	{
		write(2, "Cannot get the current directory ... !\n",
			ft_strlen("Cannot get the current directory ... !\n"));
		g_exit_status = 1;
	}
	if (cmd && cmd->arg[1])
	{
		if (ft_strcmp(cmd->arg[1], "-p") == 0 || cmd->arg[1][0] == '-')
		{
			display_pwd(cmd);
			g_exit_status = 2;
			return ;
		}
	}
	else
	{
		write(1, buffer, ft_strlen(buffer));
		g_exit_status = 0;
	}
	write(1, "\n", 1);
}
