/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:13:59 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/01 14:34:01 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_redir(t_command *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if ((redir->type == T_RED_IN || redir->type == T_HERDOC)
			&& strcmp(redir->name, "/dev/stdin") != 0)
		{
			dup2(redir->fd_in, STDIN_FILENO);
			close(redir->fd_in);
		}
		else if ((redir->type == T_RED_OUT || redir->type == T_RED_OUT_APEND)
			&& strcmp(redir->name, "/dev/stdout") != 0)
		{
			dup2(redir->fd_out, STDOUT_FILENO);
			close(redir->fd_out);
		}
		redir = redir->next;
	}
}

static int	helper(t_env **envp, t_command *cmd, char *res)
{
	char	**env;

	env = get_envp(*envp);
	execve(res, cmd->arg, env);
	perror(cmd->arg[0]);
	free(env);
	ft_clean(envp);
	g_exit_status = 127;
	exit(g_exit_status);
	return (0);
}

int	first_command(t_command *cmd, t_env **envp, t_pipes p)
{
	char	*res;

	check_file_status(cmd, envp);
	dup2(p.fd[1], STDOUT_FILENO);
	if (cmd->redir)
		check_redir(cmd);
	close(p.fd[0]);
	close(p.fd[1]);
	if (is_buitins(cmd))
	{
		execute_buitlins(envp, cmd);
		exit(g_exit_status);
	}
	if (!cmd || !cmd->arg || !cmd->arg[0])
		exit(g_exit_status);
	res = helper_check_path(cmd, *envp);
	if (!res)
	{
		write(1, "command not found\n", 18);
		g_exit_status = 127;
		exit(g_exit_status);
	}
	return (helper(envp, cmd, res));
}

int	last_command(t_command *cmd, t_env **envp, t_pipes p)
{
	char	*res;

	if (check_file_status(cmd, envp) && cmd->redir)
		check_redir(cmd);
	close(p.fd[0]);
	close(p.fd[1]);
	if (is_buitins(cmd))
	{
		execute_buitlins(envp, cmd);
		exit(g_exit_status);
	}
	if (!cmd || !cmd->arg || !cmd->arg[0])
		exit(g_exit_status);
	res = helper_check_path(cmd, *envp);
	if (!res)
	{
		write(1, "command not found\n", 18);
		g_exit_status = 127;
		exit(g_exit_status);
	}
	return (helper(envp, cmd, res));
}

int	mid_command(t_command *cmd, t_env **envp, t_pipes p)
{
	char	*res;

	check_file_status(cmd, envp);
	dup2(p.fd[1], STDOUT_FILENO);
	if (cmd->redir)
		check_redir(cmd);
	close(p.fd[0]);
	close(p.fd[1]);
	if (is_buitins(cmd))
	{
		execute_buitlins(envp, cmd);
		exit(g_exit_status);
	}
	if (!cmd || !cmd->arg || !cmd->arg[0])
		exit(g_exit_status);
	res = helper_check_path(cmd, *envp);
	if (!res)
	{
		write(1, "command not found\n", 18);
		g_exit_status = 127;
		exit(g_exit_status);
	}
	return (helper(envp, cmd, res));
}
