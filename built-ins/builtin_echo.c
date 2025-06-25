/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:07:42 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/25 22:20:08 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_option(t_command *cmd)
{
	int	j;

	if (cmd->arg[1] && cmd->arg[1][0] == '-' && cmd->arg[1][1] == 'n')
	{
		j = 2;
		while (cmd->arg[1][j] == 'n')
			j++;
		if (cmd->arg[1][j] == '\0')
			return (1);
	}
	return (0);
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
	int	fd;

	fd = 1;
	i = 1;
	newline = 1;
	if (cmd && cmd->redir)
	{
		if (open_file(cmd) == -1)
		{
			printf("1\n");
			g_exit_status = 1;
			return ;
		}
	}
	if (check_option(cmd))
	{
		newline = 0;
		i++;
	}
	write_echo(cmd, i);
	if (newline)
		write(fd, "\n", 1);
	g_exit_status = 0;
}
