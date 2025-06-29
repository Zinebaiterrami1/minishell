/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:38:54 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/29 05:03:54 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		write(1, ".: filename argument required\n", 1);
		write(1, ".: usage: . filename [arguments]\n", 1);
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
	free(envp);
	ft_clean(&env);
	perror(cmd->arg[0]);
	g_exit_status = 127;
	exit(g_exit_status);
}

void	helper_pipes(t_command *cmd, t_env **envp, t_pipes p)
{
	if (check_file_status(cmd, envp) && cmd->redir
		&& (cmd->redir->type == T_RED_IN))
	{
		dup2(cmd->redir->fd_in, STDIN_FILENO);
		close(cmd->redir->fd_in);
	}
	if (check_file_status(cmd, envp) && cmd->redir
		&& (cmd->redir->type == T_RED_OUT
			|| cmd->redir->type == T_RED_OUT_APEND))
	{
		dup2(cmd->redir->fd_out, STDOUT_FILENO);
		close(cmd->redir->fd_out);
	}
	else
	{
		dup2(p.fd[1], STDOUT_FILENO);
		close(p.fd[0]);
		close(p.fd[1]);
	}
}

void	helper_pipes1(t_command *cmd, t_env **envp)
{
	if (check_file_status(cmd, envp) && cmd->redir)
	{
		if (cmd->redir->type == T_RED_IN)
		{
			dup2(cmd->redir->fd_in, STDIN_FILENO);
			close(cmd->redir->fd_in);
		}
		if (cmd->redir->type == T_RED_OUT
			|| cmd->redir->type == T_RED_OUT_APEND)
		{
			dup2(cmd->redir->fd_out, STDOUT_FILENO);
			close(cmd->redir->fd_out);
		}
	}
}
