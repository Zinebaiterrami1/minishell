/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:24:16 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/25 16:10:13 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getpath(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->env_key, "PATH") == 0)
		{
			return (tmp->env_value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	**split_path(t_env *lst)
{
	char	*path;
	char	**sp;

	path = ft_getpath(lst);
	if (!path)
	{
		return (NULL);
	}
	sp = ft_split(path, ':');
	return (sp);
}

char	*search_cmd(t_command *cmd, t_env *lst)
{
	char	*join;
	char	*joinpath;
	int		i;
	char	**sp;

	i = 0;
	sp = split_path(lst);
	if (!sp)
	{
		joinpath = ft_strjoin("./", cmd->arg[0]);
		printf("joinpath; %s\n", cmd->arg[0]);
		return (joinpath);
	}
	join = ft_strjoin("/", cmd->arg[0]);
	while (sp[i])
	{
		joinpath = ft_strjoin(sp[i], join);
		if (access(joinpath, F_OK | X_OK) == 0)
			return (joinpath);
		i++;
	}
	return (NULL);
}
