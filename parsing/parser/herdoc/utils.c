/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:47:30 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/25 15:32:56 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_herdoc	*init_herdoc(t_env **envp)
{
	t_herdoc	*herdoc;

	herdoc = gc_malloc(sizeof(t_herdoc), getter());
	memset(herdoc, 0, sizeof(t_herdoc));
	herdoc->env = envp;
	return (herdoc);
}

static int	open_herd_file(t_herdoc *herdoc)
{
	char	*path;
	int		i;

	i = 0;
	path = gc_strdup("/tmp/herdoc_");
	while (1)
	{
		if (access(path, F_OK) != 0)
			break ;
		path = ft_strjoin(path, ft_itoa(i));
		i++;
	}
	herdoc->fd = open(path, O_CREAT | O_RDWR, 0644);
	herdoc->file_name = path;
	return (herdoc->fd);
}

static int	exit_failure(char *msg)
{
	perror(msg);
	return (EXIT_FAILURE);
}

void	*herdoc_check(t_herdoc **herdoc, t_env **env)
{
	*herdoc = init_herdoc(env);
	if (!*herdoc)
		return (NULL);
	if (open_herd_file(*herdoc) < 0)
	{
		exit_failure("open failed");
		return (NULL);
	}
	return (herdoc);
}
