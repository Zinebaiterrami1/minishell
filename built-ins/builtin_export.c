/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:34:56 by zait-err          #+#    #+#             */
/*   Updated: 2025/05/25 17:32:26 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_valid_identifier(const char *str)
{
	int i = 0;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void update_or_add_env(t_env **env, char *key, char *value)
{
	t_env *tmp = *env;

	while (tmp)
	{
		if (ft_strcmp(tmp->env_key, key) == 0)
		{
			free(tmp->env_value);
			tmp->env_value = value ? ft_strdup(value) : NULL;
			return ;
		}
		tmp = tmp->next;
	}
	// Add new node
	t_env *new = malloc(sizeof(t_env));
	new->env_key = ft_strdup(key);
	new->env_value = value ? ft_strdup(value) : NULL;
	new->next = NULL;
	// add to end
	tmp = *env;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		*env = new;
}

static void print_export(t_env *env)
{
	while (env)
	{
		printf("declare -x %s\n", env->line);
		// if (env->env_value)
		// 	printf("=\"%s\"", env->env_value);
		// printf("\n");
		env = env->next;
	}
}

void ft_export(t_env **env, t_command **args)
{
	int i = 1;
	char *key;
	char *value;
	char *equal;
    t_command *tmp;
    
    tmp = *args;
	if (!tmp->arg[1])
		return print_export(*env);
	while (tmp->arg[i])
	{
		if (!is_valid_identifier(tmp->arg[i]))
			printf("export: `%s`: not a valid identifier\n", tmp->arg[i]);
		else
		{
			equal = ft_strchr(tmp->arg[i], '=');
			if (equal)
			{
				key = ft_substr(tmp->arg[i], 0, equal - tmp->arg[i]);
				value = ft_strdup(equal + 1);
			}
			else
			{
				key = ft_strdup(tmp->arg[i]);
				value = NULL;
			}
			update_or_add_env(env, key, value);
			free(key);
			if (value)
				free(value);
		}
		i++;
	}
}
