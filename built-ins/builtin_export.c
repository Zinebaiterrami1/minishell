/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:34:56 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/29 23:16:19 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	add_export_var(t_env **env, char *arg)
{
	char	*key;
	char	*value;
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (equal)
	{
		key = ft_substr(arg, 0, equal - arg);
		value = ft_strdup(equal + 1);
		if (!*key)
		{
			ft_putstr_fd("export: ", 1);
			ft_putstr_fd(arg, 1);
			ft_putstr_fd(": not a valid identifier\n", 1);
			free_key_value(key, value);
			return ;
		}
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	set_env_value(env, key, value);
}

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (ft_isdigit(str[0]) == 1)
			break ;
		while (ft_isalpha(str[i]) == 1 || ft_isdigit(str[i]) == 1
			|| str[i] == '_')
			i++;
		if (str[i] == '=' || str[i] == '\0')
			return (1);
		else if (str[i] == '+' && str[i + 1] == '=')
		{
			g_exit_status = 0;
			return (0);
		}
		break ;
	}
	g_exit_status = 1;
	return (0);
}

void	handle_export_args(t_env **env, t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->arg[i])
	{
		if (!is_valid_identifier(cmd->arg[i]))
		{
			ft_putstr_fd("export: ", 1);
			ft_putstr_fd(cmd->arg[i], 1);
			ft_putstr_fd(": not a valid identifier\n", 1);
		}
		else
			add_export_var(env, cmd->arg[i]);
		i++;
	}
}

void	ft_export(t_env **env, t_command **args)
{
	t_command	*cmd;

	cmd = *args;
	if (!cmd->arg[1])
		print_export(*env);
	else
		handle_export_args(env, cmd);
}
