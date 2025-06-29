/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:07:42 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/29 04:16:56 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_option(t_command *cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->arg[i])
	{
		if (cmd->arg[i][0] == '-' && cmd->arg[i][1] == 'n')
		{
			j = 2;
			while (cmd->arg[i][j] == 'n')
				j++;
			if (cmd->arg[i][j] != '\0')
				break ;
			i++;
		}
		else
			break ;
	}
	return (i);
}

static void	write_echo(t_command *cmd, int start)
{
	int	i;
	int	fd;

	fd = 1;
	i = start;
	while (cmd->arg[i])
	{
		write(fd, cmd->arg[i], ft_strlen(cmd->arg[i]));
		if (cmd->arg[i + 1])
			write(fd, " ", 1);
		i++;
	}
}

void	ft_echo(t_command *cmd)
{
	int	newline;
	int	i;

	newline = 1;
	if (cmd && cmd->redir)
	{
		if (open_file(cmd) == -1)
		{
			g_exit_status = 1;
			return ;
		}
	}
	if (cmd->arg[1][0] == '-')
	{
		newline = 0;
	}
	i = check_option(cmd);
	write_echo(cmd, i);
	if (newline)
		write(1, "\n", 1);
	g_exit_status = 0;
}
