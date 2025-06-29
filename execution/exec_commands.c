/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:13:59 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/30 00:38:37 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_file_status(t_command *file, t_env **env)
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
		return(1);
	}
	return (1);
}

static void	check_redir(t_command *cmd, t_pipes *p, int last)
{
	if (cmd->redir->type == T_RED_IN)
	{
		if(ft_strcmp(cmd->redir->name, "/dev/stdin") == 0)
			dup2(p->fd[0], STDIN_FILENO);
		else
			dup2(cmd->redir->fd_in, STDIN_FILENO);
		close(cmd->redir->fd_in);
	}
	if ((cmd->redir->type == T_RED_OUT
			|| cmd->redir->type == T_RED_OUT_APEND))
	{
		if(ft_strcmp(cmd->redir->name, "/dev/stdout") == 0)
			dup2(p->fd[1], STDOUT_FILENO);
		else
			dup2(cmd->redir->fd_out, STDOUT_FILENO);
		close(cmd->redir->fd_out);
	}
	else if(!last)
		dup2(p->fd[1], STDOUT_FILENO);
}

int	first_command(t_command *cmd, t_env **envp, t_pipes p)
{
	char	*res;

	check_file_status(cmd, envp);
	if (cmd->redir)
		check_redir(cmd, &p, 0);
	else
		dup2(p.fd[1], STDOUT_FILENO);
	close(p.fd[0]);
	close(p.fd[1]);
	if(is_buitins(cmd))
	{
		execute_buitlins(envp, cmd);
		exit(g_exit_status);
	}
	if(!cmd || !cmd->arg || !cmd->arg[0])
		exit(g_exit_status);
	res = search_cmd(cmd, *envp);
	if (!res)
	{
		write(1, "command not found\n", 18);
		g_exit_status = 127;
		exit(g_exit_status);
	}
	execve(res, cmd->arg, get_envp(*envp));
	return (0);
}

int	last_command(t_command *cmd, t_env **envp, t_pipes p)
{
	char	*res;

	if (check_file_status(cmd, envp) && cmd->redir)
		check_redir(cmd, &p, 1);
	close(p.fd[0]);
	close(p.fd[1]);
	if(is_buitins(cmd))
	{
		execute_buitlins(envp, cmd);
		exit(g_exit_status);
	}
	if(!cmd || !cmd->arg || !cmd->arg[0])
		exit(g_exit_status);
	res = search_cmd(cmd, *envp);
	if (!res)
	{
		write(1, "command not found\n", 18);
		g_exit_status = 127;
		exit(g_exit_status);
	}
	execve(res, cmd->arg, get_envp(*envp));
	return (0);
}

int	mid_command(t_command *cmd, t_env **envp, t_pipes p)
{
	char	*res;

	check_file_status(cmd, envp);
	if (cmd->redir)
			check_redir(cmd, &p, 0);
	else
		dup2(p.fd[1], STDOUT_FILENO);
	close(p.fd[0]);
	close(p.fd[1]);
	if(is_buitins(cmd))
	{
		execute_buitlins(envp, cmd);
		exit(g_exit_status);
	}
	if(!cmd || !cmd->arg || !cmd->arg[0])
		exit(g_exit_status);
	res = search_cmd(cmd, *envp);
	if (!res)
	{
		write(1, "command not found\n", 18);
		g_exit_status = 127;
		exit(g_exit_status);
	}
	execve(res, cmd->arg, get_envp(*envp));
	return (0);
}
