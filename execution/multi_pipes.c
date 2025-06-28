/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:23:55 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/28 11:54:56 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static pid_t	close_fd(t_pipes *p)
{
	dup2(p->fd[0], STDIN_FILENO);
	close(p->fd[0]);
	close(p->fd[1]);
	return (p->pid);
}

static int	helper6(t_command *cmd, t_env **envp, int curr_cmd, t_pipes *p)
{
	int	error;

	if (is_buitins(cmd))
	{
		execute_buitlins(envp, cmd);
		exit(g_exit_status);
	}
	else if (curr_cmd == 0)
		error = first_command(cmd, envp, *p);
	else if (curr_cmd == p->nb_cmd - 1)
		error = last_command(cmd, envp, *p);
	else
		error = mid_command(cmd, envp, *p);
	return (error);
}

pid_t	global_pipes(t_command *cmd, t_env **envp, int curr_cmd, t_pipes *p)
{
	int	error;

	error = 1;
	ignore_signals();
	p->pid = fork();
	if (p->pid == -1)
	{
		perror("fork failed\n");
		return (-1);
	}
	if (p->pid == 0)
	{
		setup_signals_child();
		error = helper6(cmd, envp, curr_cmd, p);
	}
	if (error == 0)
	{
		g_exit_status = 1;
		return (g_exit_status);
	}
	close_fd(p);
	return (p->pid);
}

int	wait_children(t_pipes *p)
{
	int	status;
	int	i;
	int	sig;

	i = 0;
	status = 0;
	waitpid(p->pid, &status, 0);
	while (i < p->nb_cmd - 1)
	{
		wait(NULL);
		i++;
	}
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			write(1, "Quit (core dumped)\n", 20);
		g_exit_status = 128 + sig;
	}
	return (g_exit_status);
}

void	*multiple_pipes(t_env **env, t_command *list)
{
	int		curr_cmd;
	t_pipes	p;

	curr_cmd = 0;
	p.nb_cmd = ft_lstsizee(list);
	while (list && curr_cmd < p.nb_cmd)
	{
		if (pipe(p.fd) == -1)
		{
			perror("pipe failed\n");
			return (NULL);
		}
		p.pid = global_pipes(list, env, curr_cmd, &p);
		if (p.pid == -1)
			return (NULL);
		list = list->next_com;
		curr_cmd++;
	}
	wait_children(&p);
	return ("success\n");
}
