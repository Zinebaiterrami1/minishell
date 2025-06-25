/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:13:59 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/25 15:56:12 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void check_file_status(t_command *file, t_env **env)
{
	(void)env;
	if(!file)
		return ;
	if(file->redir)
	{
		if (open_file(file) == -1)
		{
			g_exit_status = 1;
			ft_clean(env);
			free_all(getter());
			exit(g_exit_status);
		}
	}
}

int	first_command(t_command *cmd, t_env **envp, t_pipes p)
{
	char *res;

	res = search_cmd(cmd, *envp);
	check_file_status(cmd, envp);
	dup2(p.fd[1], STDOUT_FILENO);
	close(p.fd[0]);
	close(p.fd[1]);
	if(!res)
	{
		printf("command not found!!!!!!\n");
		g_exit_status = 127;
	}
	execve(res, cmd->arg, get_envp(*envp));
	return (0); 	
}

int	last_command(t_command *cmd, t_env **envp, t_pipes p)
{
	char *res;

	res = search_cmd(cmd, *envp);
	check_file_status(cmd, envp);
	close(p.fd[0]);
	close(p.fd[1]);
	if(!res)
	{
		printf("command not found!\n");
		g_exit_status = 127;
		exit(127);
	}
	execve(res, cmd->arg, get_envp(*envp));
	return (0);
}

int	mid_command(t_command *cmd, t_env **envp, t_pipes p)
{
	char *res;

	res = search_cmd(cmd, *envp);
	check_file_status(cmd, envp);
	dup2(p.fd[1], STDOUT_FILENO);
	close(p.fd[0]);
	close(p.fd[1]);
	if(!res)
	{
		printf("command not found!\n");
		g_exit_status = 127;
		exit(127);
	}
	execve(res, cmd->arg, get_envp(*envp));
	return (0);
}
