/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:36 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/25 22:22:14 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_command *cmd)
{
	char	buffer[BUFFER_SIZE];

	if (getcwd(buffer, BUFFER_SIZE) == NULL)
	{
		write(2, "Cannot get the current directory ... !\n",
			ft_strlen("Cannot get the current directory ... !\n"));
		printf("6\n");
		g_exit_status = 1;
	}
	if (cmd && cmd->arg[1])
	{
		if (ft_strcmp(cmd->arg[1], "-p") == 0 || cmd->arg[1][0] == '-')
		{
			printf("bash: pwd: %s: invalid option\n", cmd->arg[1]);
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
