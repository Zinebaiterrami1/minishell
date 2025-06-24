/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:47:37 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/24 02:32:57 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	write_export(t_env *min)
{
	if (!min->env_value)
		printf("declare -x %s\n", min->env_key);
	else
		printf("declare -x %s=\"%s\"\n", min->env_key, min->env_value);
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