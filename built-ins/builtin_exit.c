/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:22 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/14 17:59:17 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_is_numeric(char *str)
{
	int	i = 0;

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

// void ft_exit(t_command *cmd)
// {
// 	int status;

// 	if(!cmd->arg[1])
// 	{
// 		write(1, "exit\n", 5);
// 		exit(0);
// 	}
// 	if(cmd->arg[1])
// 	{
// 		if(!ft_is_numeric(cmd->arg[1]))
// 		{
// 			printf("minishell: exit: %s: numeric argument required\n", cmd->arg[1]);
// 			exit(255);
// 		}
// 	}
// 	if(cmd->arg[2])
// 	{
// 		printf("minishell: exit: too many arguments\n");
// 		return ;
// 	}
// 	write(1, "exit\n", 5);
// 	status = ft_atoi(cmd->arg[1]);
// 	exit(status % 256);
// }

//new version usin exit status, global variable
void ft_exit(t_command *cmd)
{
	int status;

	write(1, "exit\n", 5);
	if(!cmd->arg[1])
	{
		g_exit_status = 0;
		exit(g_exit_status);
	}
	if(!ft_is_numeric(cmd->arg[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->arg[1], STDERR_FILENO);
		ft_putstr_fd(":numeric argument required\n", STDERR_FILENO);
		g_exit_status = 2;
		exit(g_exit_status);
	}
	if(cmd->arg[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_exit_status = 1;
		return;
	}
	status = ft_atoi(cmd->arg[1]);
	g_exit_status = status % 256;
	exit(g_exit_status);
}