/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:47:37 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/29 04:45:40 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	write_export(t_env *min)
{
	if (!min->env_value)
	{
		ft_putstr_fd("declare -x", 1);
		ft_putstr_fd(min->env_key, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		ft_putstr_fd("declare -x", 1);
		ft_putstr_fd(min->env_key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(min->env_value, 1);
		ft_putstr_fd("\"\n", 1);
	}
}

void	print_export(t_env *export)
{
	t_env	*min;
	t_env	*current;
	int		size;

	size = ft_lstsize(export);
	while (size > 0)
	{
		min = export;
		while (min->is_printed)
			min = min->next;
		current = min->next;
		while (current)
		{
			if (ft_strcmp(current->env_key, min->env_key) < 0
				&& current->is_printed == 0)
			{
				min = current;
			}
			current = current->next;
		}
		min->is_printed = 1;
		write_export(min);
		size--;
	}
}

void	free_key_value(char *key, char *value)
{
	free(key);
	if (value)
		free(value);
}
