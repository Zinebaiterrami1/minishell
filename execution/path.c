/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:24:16 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/24 02:15:54 by nel-khad         ###   ########.fr       */
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
	if(!path)
	{
		return (NULL);
	}
	sp = ft_split(path, ':');
	return (sp);
}

// static char	*utils1(t_command *cmd)
// {
// 	if (ft_strchr(cmd->arg[0], '/'))
// 	{
// 		if (access(cmd->arg[0], F_OK | X_OK) == 0)
// 			return (cmd->arg[0]);
// 	}
// 	return (NULL);
// }

char	*search_cmd(t_command *cmd, t_env *lst)
{
	char	*join;
	char	*joinpath;
	int		i;
	char	**sp;

	i = 0;
	//utils1(cmd);
	sp = split_path(lst);
	if(!sp)
	{
		// if(access(cmd->arg[0], F_OK) != 0)
		// {
			printf("command not found\n");
			g_exit_status = 127;
			exit(g_exit_status);
		// }	
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





//wax cmd fiha / --> eayt l stat xf wax directory else check wax acces = 0 