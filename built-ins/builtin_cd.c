/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:07:52 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/02 11:00:28 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verify_permission(t_command *cmd)
{
	if (access(cmd->arg[1], F_OK) == -1)
	{
		g_exit_status = 127;
		return (0);
	}
	if (access(cmd->arg[1], X_OK) == -1)
	{
		g_exit_status = 126;
		return (0);
	}
	return (g_exit_status);
}

int	ft_cd(t_command *cmd, t_env **env)
{
	char	*old_path;
	char	*new_path;

	if (!cmd->arg[1])
	{
		write(1, "must be a relative or absolute path\n", 36);
		return (-1);
	}
	if(cmd->arg[2])
	{
		write(1, " cd: too many arguments\n", 24);
		return (-1);
	}
	old_path = getcwd(NULL, 0);
	if (chdir(cmd->arg[1]) != 0)
	{
		perror("cd");
		verify_permission(cmd);
	}
	new_path = getcwd(NULL, 0);
	set_env_value(env, "PWD", new_path);
	set_env_value(env, "OLDPWD", old_path);
	free(new_path);
	free(old_path);
	return (0);
}


