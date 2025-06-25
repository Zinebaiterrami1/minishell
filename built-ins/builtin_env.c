/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:14 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/24 21:24:14 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*head;
	t_env	*tmp;
	t_env	*new_node;

	head = NULL;
	tmp = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		new_node->line = envp[i];
		new_node->env_key = NULL;
		new_node->env_value = NULL;
		new_node->next = NULL;
		if (!head)
			head = new_node;
		else
			tmp->next = new_node;
		tmp = new_node;
		i++;
	}
	return (head);
}

void	update_line(t_env *node)
{
	char	*tmp;
	char	*newline;

	if (!node || !node->env_key)
		return ;
	if (node->env_value)
	{
		tmp = ft_strjoin(node->env_key, "=");
		if (!tmp)
			return ;
		newline = ft_strjoin(tmp, node->env_value);
		if (!newline)
			return ;
	}
	else
	{
		newline = ft_strdup(node->env_key);
		if (!newline)
			return ;
	}
	node->line = newline;
}

void    set_env_value(t_env **env_list, char *key, char *value)
{
    t_env    *tmp;
    t_env    *new_node;
    char    *new_value;

    new_value = NULL;
    if (!*env_list || !env_list)
        return ;
    tmp = *env_list;
    if(ft_new_value(tmp, key, value, new_value))
        return ; //updated, dont add new node
    new_node = ft_lstnew(key, value);
    if (!new_node)
        return ;
    update_line(new_node);
    ft_lstadd_backk(env_list, new_node);
}

t_env	*split_env(t_env *lst)
{
	t_env	*tmp;
	char	*equal_env;
	int		key_len;

	tmp = lst;
	while (tmp)
	{
		equal_env = ft_strchr(tmp->line, '=');
		key_len = equal_env - tmp->line;
		tmp->env_key = ft_substr(tmp->line, 0, key_len);
		tmp->env_value = ft_strdup(equal_env + 1);
		tmp = tmp->next;
	}
	return (lst);
}