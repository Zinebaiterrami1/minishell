/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:16:07 by zait-err          #+#    #+#             */
/*   Updated: 2025/07/01 21:37:33 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_file_pipes(t_command *cmd)
{
	t_redir	*r;

	r = cmd->redir;
	while (r)
	{
		if (r->name)
		{
			if (r->type == T_RED_IN)
				r->fd_in = open(r->name, O_RDONLY);
			else if (r->type == T_HERDOC)
				r->fd_in = open(r->herdoc->file_name, O_RDONLY);
			else if (r->type == T_RED_OUT)
				r->fd_out = open(r->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (r->type == T_RED_OUT_APEND)
				r->fd_out = open(r->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (r->fd_out == -1 || r->fd_in == -1)
			{
				perror(r->name);
				return (-1);
			}
		}
		r = r->next;
	}
	return (0);
}

int	open_file(t_command *cmd)
{
	t_redir	*r;

	r = cmd->redir;
	while (r)
	{
		if (r->name)
		{
			if (r->type == T_RED_IN)
				r->fd_in = open(r->name, O_RDONLY);
			else if (r->type == T_HERDOC)
				r->fd_in = open(r->herdoc->file_name, O_RDONLY);
			else if (r->type == T_RED_OUT)
				r->fd_out = open(r->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (r->type == T_RED_OUT_APEND)
				r->fd_out = open(r->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (r->fd_out == -1 || r->fd_in == -1)
			{
				perror(r->name);
				return (-1);
			}
			dup2_close(r);
		}
		r = r->next;
	}
	return (0);
}

void	dup2_close(t_redir *r)
{
	if (r->fd_in != 0)
		dup2(r->fd_in, 0);
	if (r->fd_out != 1)
		dup2(r->fd_out, 1);
	if (r->fd_in > 2)
		close(r->fd_in);
	if (r->fd_out > 2)
		close(r->fd_out);
}

int	check_file_status(t_command *file, t_env **env)
{
	(void)env;
	if (!file)
		return (0);
	if (file->redir)
	{
		if (open_file_pipes(file) == -1)
		{
			g_exit_status = 1;
			ft_clean(env);
			exit(g_exit_status);
		}
		return (1);
	}
	return (1);
}

// if(!r->name || !cmd->redir)
// 	return (-1);