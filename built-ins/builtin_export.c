/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:34:56 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/14 23:42:46 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int is_valid_identifier(const char *str)
// {
// 	int i = 0;

// 	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
// 		return (0);
// 	while (str[i] && str[i] != '=')
// 	{
// 		if (!ft_isalnum(str[i]) && str[i] != '_')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

static void	free_key_value(char *key, char *value)
{
	free(key);
	if (value)
		free(value);
}


static void	add_export_var(t_env **env, char *arg)
{
	char	*key;
	char	*value;
	char	*equal;
	// t_env 	*tmp;

	// tmp = *env;
	equal = ft_strchr(arg, '=');
	if (equal)
	{
		printf("with value = value\n");
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
		printf("with value = null\n");
		key = ft_strdup(arg);
		value = NULL;
	}
	// check_dup(tmp, &arg);
	set_env_value(env, key, value);
}

int is_valid_identifier(char *str)
{
	int i;
	
	i = 0;
	while(str[i] != '=' && str[i] != '\0')
	{
		if(ft_isdigit(str[0]) == 1)
			break;
		while(ft_isalpha(str[i]) == 1 || ft_isdigit(str[i]) == 1 || str[i] == '_')
			i++;
		if(str[i] == '=' || str[i] == '\0')
			return (1);
		else if(str[i] == '+' && str[i + 1] == '=')
		{
			printf("am here inside is_valid_identifier\n");
			g_exit_status = 0;
			return (0);
		}
		break;
	}
	g_exit_status = 1;
	return (0);
}

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
			// printf("key: %s, value: %s, line: %s\t", min->env_key, min->env_value, min->line);
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

// static int check_dup(t_env *lst, char **arg)
// {
// 	// t_command *tmp;
// 	t_env *current;
// 	char *equal;
// 	char *key;
	
// 	current = lst;
// 	int i = 1;

// 	while(arg[i])
// 	{	
// 		equal = ft_strchr(arg[i], '=');
// 		if(equal)
// 		{			
// 			key = ft_substr(arg[i], 0, equal - arg[i]);
// 			current = lst;
// 			while(current)
// 			{
// 				if(ft_strcmp(key, current->env_key) == 0)
// 				{
// 					free(key);
// 					return (1);
// 				}
// 				current = current->next;
// 			}
// 			free (key);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

void	handle_export_args(t_env **env, t_command *cmd)
{
	int	i;
	
	i = 1;
	while (cmd->arg[i])
	{
		
		if (!is_valid_identifier(cmd->arg[i]))
		{
			printf("export: `%s`: not a valid identifier\n", cmd->arg[i]);
		}
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
		//printf("after adding new node to the list\n");
		//printf("call print_export after addin new node--------------------------------------------: \n");
		//print_test(*env);
		print_export(*env);	
		//printf("===============================\n");
		g_exit_status = 0;
		return ;
	}
	//print_test(*env);
	handle_export_args(env, cmd);
	printf("after --------------------\n");
	//print_test(*env);
	//printf("ft_export-----------------------------------\n");
}
