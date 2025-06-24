/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:13:59 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/24 02:15:23 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	first_command(t_command *cmd, t_env **envp, t_pipes p)
{
	char *res;

	res = search_cmd(cmd, *envp);
	if (cmd->redir)
	{
		if (open_file(cmd) == -1)
			return (-1);
	}
	else
	{
		dup2(p.fd[1], STDOUT_FILENO);
		close(p.fd[0]);
		close(p.fd[1]);
	}
	if(!res)
	{
		printf("command not found!!!!!!\n");
		g_exit_status = 127;
	}
	execve(res, cmd->arg, get_envp(*envp));
	return (0); //
}

int	last_command(t_command *cmd, t_env **envp, t_pipes p)
{
	char *res;

	res = search_cmd(cmd, *envp);
	if (cmd->redir)
	{
		if (open_file(cmd) == -1)
			return (-1);
	}
	else
	{
		dup2(STDOUT_FILENO, p.fd[0]);
		close(p.fd[0]);
		close(p.fd[1]);
	}
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
	if (cmd->redir)
	{
		if (open_file(cmd) == -1)
			return (-1);
	}
	else
	{
		dup2(p.fd[1], STDOUT_FILENO);
		close(p.fd[0]);
		close(p.fd[1]);
	}
	if(!res)
	{
		printf("command not found!\n");
		g_exit_status = 127;
		exit(127);
	}
	execve(res, cmd->arg, get_envp(*envp));
	return (0);
}