/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:22 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/29 04:17:01 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_command *cmd)
{
	int	status;

	write(1, "exit\n", 5);
	if (!cmd->arg[1])
		exit(g_exit_status);
	if (!ft_is_numeric(cmd->arg[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->arg[1], STDERR_FILENO);
		ft_putstr_fd(":numeric argument required\n", STDERR_FILENO);
		g_exit_status = 2;
		exit(g_exit_status);
	}
	if (cmd->arg[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_exit_status = 1;
		return ;
	}
	status = ft_atoi(cmd->arg[1]);
	g_exit_status = status % 256;
	exit(g_exit_status);
}
