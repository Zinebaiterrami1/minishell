/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:40 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/25 22:22:38 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	remove_env_key(t_env **env, char *key)
{
	t_env	*current;
	t_env	*previous;

	current = *env;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->env_key, key) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				*env = current->next;
			free(current->env_key);
			free(current->env_value);
			free(current);
			break ;
		}
		previous = current;
		current = current->next;
	}
}

void	ft_unset(t_command **cmd, t_env **env)
{
	t_command	*tmp;
	int			i;

	tmp = *cmd;
	i = 1;
	if (!tmp->arg[1])
	{
		printf("7\n");
		g_exit_status = 1;
		return ;
	}
	while (tmp->arg[i])
		remove_env_key(env, tmp->arg[i++]);
	g_exit_status = 0;
}
