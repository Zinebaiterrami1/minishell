/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:47:30 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/20 19:56:36 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static  int	has_quotes(t_token *token)
{
	if (token->type == T_D_COTS || token->type == T_S_COTS)
		return (1);
	return (0);
}

static void helper(char **line, t_token *token)
{
	if(!*line)
		ft_putstr_fd("warning: here-document at line delimited by end-of-file\n",
		2);
	else if(!ft_strcmp(*line, token->value))
		free(*line);			
}


static void helper_2(t_herdoc *herdoc, char **line, t_token *token)
{
	if(!has_quotes(token))
	{
		*line = herdoc_expand(*line, herdoc);
		ft_putstr_fd(ft_strjoin(*line, "\n"), herdoc->fd);
	}
	else
	{
		ft_putstr_fd(ft_strjoin(*line, "\n"), herdoc->fd);
		free(*line);
	}
}

int	handel_herdoc(t_env **env, t_token *token, t_redir *redir)
{
	char	*line;

	if(!herdoc_check(&redir->herdoc, env))
		return(EXIT_FAILURE);
	while (1)
	{
		line = readline("herdoc>");
		if (!line || !ft_strcmp(line, token->value))
		{
			helper(&line, token);
			break ;
		}
		helper_2(redir->herdoc, &line, token);
	}
	close(redir->herdoc->fd);
	return (EXIT_SUCCESS);
}
