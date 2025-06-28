/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:13:59 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/28 11:34:58 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_file_status(t_command *file, t_env **env)
{
	(void)env;
	if (!file)
		return (0);
	if (file->redir)
	{
		if (open_file(file) == -1)
		{
			g_exit_status = 1;
			ft_clean(env);
			exit(g_exit_status);
		}
	}
	return (1);
}

static void	helper5(t_command *cmd)
{
	if (cmd->redir->type == T_RED_IN)
	{
		dup2(cmd->redir->fd_in, STDIN_FILENO);
		close(cmd->redir->fd_in);
	}
	if ((cmd->redir->type == T_RED_OUT
			|| cmd->redir->type == T_RED_OUT_APEND))
	{
		dup2(cmd->redir->fd_out, STDOUT_FILENO);
		close(cmd->redir->fd_out);
	}
}

int	first_command(t_command *cmd, t_env **envp, t_pipes p)
{
	char	*res;

	res = search_cmd(cmd, *envp);
	if (check_file_status(cmd, envp))
	{
		if (cmd->redir)
			helper5(cmd);
		else
			dup2(p.fd[1], STDOUT_FILENO);
	}
	else
		dup2(p.fd[1], STDOUT_FILENO);
	close(p.fd[0]);
	close(p.fd[1]);
	if (!res)
	{
		printf("command not found\n");
		g_exit_status = 127;
		exit(g_exit_status);
	}
	execve(res, cmd->arg, get_envp(*envp));
	return (0);
}

int	last_command(t_command *cmd, t_env **envp, t_pipes p)
{
	char	*res;

	res = search_cmd(cmd, *envp);
	if (check_file_status(cmd, envp) && cmd->redir)
		helper5(cmd);
	close(p.fd[0]);
	close(p.fd[1]);
	if (!res)
	{
		printf("command not found\n");
		g_exit_status = 127;
		exit(g_exit_status);
	}
	execve(res, cmd->arg, get_envp(*envp));
	return (0);
}

int	mid_command(t_command *cmd, t_env **envp, t_pipes p)
{
	char	*res;

	res = search_cmd(cmd, *envp);
	if (check_file_status(cmd, envp))
	{
		if (cmd->redir)
			helper5(cmd);
		else
			dup2(p.fd[1], STDOUT_FILENO);
	}
	else
		dup2(p.fd[1], STDOUT_FILENO);
	close(p.fd[0]);
	close(p.fd[1]);
	if (!res)
	{
		printf("command not found\n");
		g_exit_status = 127;
		exit(g_exit_status);
	}
	execve(res, cmd->arg, get_envp(*envp));
	return (0);
}
