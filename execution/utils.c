/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:38:54 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/19 23:42:35 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_cases(t_command *cmd, t_env *env)
{
	char	*pathcmd;

	pathcmd = search_cmd(cmd, env);
	if (ft_strcmp(pathcmd, ".") == 0)
	{
		printf(".: filename argument required\n");
		printf(".: usage: . filename [arguments]\n");
		g_exit_status = 2;
		exit(g_exit_status);
	}
	if (!pathcmd)
	{
		printf("minishell: %s command not found\n", cmd->arg[0]);
		g_exit_status = 127;
		exit(g_exit_status);
	}
	execve(pathcmd, cmd->arg, get_envp(env));
}
