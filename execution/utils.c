/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:38:54 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/26 00:02:09 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_free_env(char **envp)
{
	while (*envp)
	{
		free(*envp);
		(*envp)++;
	}
}

static char	*helper2(t_command *cmd, t_env *env)
{
	struct stat	file_stat;

	if (ft_strchr(cmd->arg[0], '/'))
	{
		if (stat(cmd->arg[0], &file_stat) == 0 && S_ISDIR(file_stat.st_mode))
		{
			ft_putstr_fd(cmd->arg[0], 1);
			ft_putstr_fd(" :Is a directory\n", 1);
			g_exit_status = 126;
			exit(g_exit_status);
		}
		else if (access(cmd->arg[0], F_OK | X_OK) == 0)
			return (cmd->arg[0]);
	}
	else if (ft_strcmp(".", cmd->arg[0]) == 0)
	{
		printf(".: filename argument required\n");
		printf(".: usage: . filename [arguments]\n");
		g_exit_status = 2;
		exit(g_exit_status);
	}
	return (search_cmd(cmd, env));
}

void	handle_cases(t_command *cmd, t_env *env)
{
	char	*pathcmd;
	char	**envp;

	pathcmd = helper2(cmd, env);
	if (!pathcmd)
	{
		ft_putstr_fd("command not found\n", 2);
		g_exit_status = 127;
		exit(g_exit_status);
	}
	envp = get_envp(env);
	execve(pathcmd, cmd->arg, envp);
	ft_clean(&env);
	ft_free_env(envp);
	perror(cmd->arg[0]);
	g_exit_status = 127;
	exit(g_exit_status);
}
