/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:59:45 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/18 21:44:19 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	write_env(t_env *env, int fd)
{
	while (env)
	{
		if (env->env_value)
		{
			write(fd, env->env_key, ft_strlen(env->env_key));
			write(fd, "=\"", 2);
			write(fd, env->env_value, ft_strlen(env->env_value));
			write(fd, "\"", 1);
			write(fd, "\n", 1);
		}
		env = env->next;
	}
}

void	ft_display_env(t_env *env, t_command *cmd)
{
	int	fd;

	fd = 1;
	if (cmd->redir)
	{
		if (open_file(cmd) == -1)
		{
			g_exit_status = 1;
			return ;
		}
	}
	if (!env)
	{
		g_exit_status = 1;
		return ;
	}
	write_env(env, fd);
	g_exit_status = 0;
}

char	*get_env_value(t_env *env_list, const char *key)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->env_key, key) == 0)
			return (tmp->env_value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_new_value(t_env *tmp, char *key, char *value, char *new_value)
{
	while (tmp)
	{
		if (ft_strcmp(tmp->env_key, key) == 0)
		{
			if (value)
			{
				new_value = ft_strdup(value);
				if (!new_value)
					return ;
				tmp->env_value = new_value;
			}
			update_line(tmp);
			return ;
		}
		tmp = tmp->next;
	}
}
