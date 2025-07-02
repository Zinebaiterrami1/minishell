/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:47:30 by nel-khad          #+#    #+#             */
/*   Updated: 2025/07/01 13:47:31 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	has_quotes(t_token *token)
{
	if (token->type == T_D_COTS || token->type == T_S_COTS)
		return (1);
	return (0);
}

static void	helper(char **line, t_token *token)
{
	(void)token;
	if (!*line)
		ft_putstr_fd("warning: here-document at "
			"line delimited by end-of-file\n",
			2);
}

static void	helper_2(t_herdoc *herdoc, char **line, t_token *token)
{
	char	*str;
	char	*tmp;

	str = NULL;
	if (!has_quotes(token))
	{
		tmp = herdoc_expand(*line, herdoc);
		free(*line);
		*line = tmp;
		str = ft_strjoin(*line, "\n");
		ft_putstr_fd(str, herdoc->fd);
		free(tmp);
		tmp = NULL;
		free(str);
		str = NULL;
	}
	else
	{
		str = ft_strjoin(*line, "\n");
		ft_putstr_fd(str, herdoc->fd);
		free(str);
		str = NULL;
	}
}

static void	read_fill(t_herdoc *herdoc, t_token *token)
{
	char	*line;

	while (1)
	{
		line = readline("herdoc>");
		if (!line || !ft_strcmp(line, token->value))
		{
			helper(&line, token);
			free(line);
			line = NULL;
			break ;
		}
		else
		{
			helper_2(herdoc, &line, token);
			line = NULL;
			free(line);
		}
	}
}

int	handel_herdoc(t_env **env, t_token *token, t_redir *redir)
{
	int	pid;
	int	status;

	if (!herdoc_check(&redir->herdoc, env))
		return (EXIT_FAILURE);
	ignore_signals();
	pid = fork();
	if (pid == -1)
		return (perror("fork() :"), EXIT_FAILURE);
	else if (pid == 0)
	{
		setup_signals_heredoc();
		read_fill(redir->herdoc, token);
		close(redir->herdoc->fd);
		exit(g_exit_status);
	}
	waitpid(pid, &status, 0);
	close(redir->herdoc->fd);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}
