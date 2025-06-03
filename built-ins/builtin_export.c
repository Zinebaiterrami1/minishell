/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:34:56 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/03 17:23:01 by zait-err         ###   ########.fr       */
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

// static void ft_print_export(t_env *env)
// {
// 	while (env)
// 	{
// 		printf("-----\n");
// 		printf("declare -x %s\n", env->line);
// 		env = env->next;
// 	}
// }

static void print_export(t_env* export)
{
	t_env *min;
	t_env *current;
	int size;

	size = ft_lstsize(export);
	
	while(size > 0)
	{
		min = export;
		while(min->is_printed)
		{
			// printf("is_printed: %d, key: %s\n", min->is_printed, min->env_key);
			min = min->next;
		}
		current = min->next;
		while(current)
		{
			if(ft_strcmp(current->env_key, min->env_key) < 0 && current->is_printed == 0)
			{
				min = current;
			}	
			current = current->next;
		}
		min->is_printed = 1;
		if(!min->env_value)
		{
			// printf("key: %s, value: %s, line: %s\t", min->env_key, min->env_value, min->line);
			printf("declare -x %s\n", min->env_key);
		}
		else
		{
			printf("key: %s, value: %s, line: %s\t", min->env_key, min->env_value, min->line);
			printf("declare -x %s=\"%s\"\n", min->env_key, min->env_value);
		}	
		size--;
	}
}

//fixed
// static void print_export(t_env *export)
// {
// 	t_env *min;
// 	t_env *current;
// 	int size;

// 	size = ft_lstsize(export);
// 	while (size > 0)
// 	{
// 		min = export;
// 		while (min && min->is_printed)
// 			min = min->next;
// 		if (!min)
// 			break;
// 		current = export;
// 		while (current)
// 		{
// 			if (ft_strcmp(current->env_key, min->env_key) < 0 && current->is_printed == 0)
// 				min = current;
// 			current = current->next;
// 		}
// 		min->is_printed = 1;
// 		printf("declare -x %s\n", min->line);
// 		size--;
// 	}
// }

// void ft_export(t_env **env, t_command **args)
// {
// 	int i;
// 	char *key;
// 	char *value;
// 	char *equal;
//     t_command *tmp;
// 	t_env *tmp1;
    
//     tmp = *args; //command list
// 	tmp1 = *env; //env list
// 	i = 1;
// 	if (!tmp->arg[1])
// 	{
// 		return print_export(tmp1); //first case of export is handled with success
// 	}
// 	while (tmp->arg[i])
// 	{	
// 		if (!is_valid_identifier(tmp->arg[i]))
// 			printf("export: `%s`: not a valid identifier\n", tmp->arg[i]);
// 		else
// 		{
// 			equal = ft_strchr(tmp->arg[i], '=');
// 			if (equal)
// 			{
// 				key = ft_substr(tmp->arg[i], 0, equal - tmp->arg[i]);
// 				value = ft_strdup(equal + 1);
// 			}
// 			else
// 			{
// 				key = ft_strdup(tmp->arg[i]);
// 				value = NULL;
// 			}
// 			set_env_value(env, key, value);
// 			free(key);
// 			if (value)
// 				free(value);
// 		}
// 		i++;
// 	}
// }

// helpers_export.c

static void	free_key_value(char *key, char *value)
{
	free(key);
	if (value)
		free(value);
}

static int check_dup(t_env *lst, char **arg)
{
	// t_command *tmp;
	t_env *current;
	char *equal;
	char *key;
	
	current = lst;
	int i = 1;

	while(arg[i])
	{	
		equal = ft_strchr(arg[i], '=');
		if(equal)
		{			
			key = ft_substr(arg[i], 0, equal - arg[i]);
			current = lst;
			while(current)
			{
				if(ft_strcmp(key, current->env_key) == 0)
				{
					free(key);
					return (1);
				}
				current = current->next;
			}
			free (key);
		}
		i++;
	}
	return (0);
}

static void	add_export_var(t_env **env, char *arg)
{
	char	*key;
	char	*value;
	char	*equal;
	t_env *tmp;

	tmp = *env;
	equal = ft_strchr(arg, '=');
	if (equal)
	{
		key = ft_substr(arg, 0, equal - arg);
		value = ft_strdup(equal + 1);
		if (!*key)
		{
			printf("export: `%s`: not a valid identifier\n", arg);
			free_key_value(key, value);
			return ;
		}
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	check_dup(tmp, &arg);
	set_env_value(env, key, value);
}

static void	handle_export_args(t_env **env, t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->arg[i])
	{
		if (!is_valid_identifier(cmd->arg[i]))
			printf("export: `%s`: not a valid identifier\n", cmd->arg[i]);
		else
			add_export_var(env, cmd->arg[i]);
		i++;
	}
}

// ft_export.c

void	ft_export(t_env **env, t_command **args)
{
	t_command	*cmd;

	cmd = *args;
	if (!cmd->arg[1])
	{
		print_export(*env);
		return ;
	}
	handle_export_args(env, cmd);
}
