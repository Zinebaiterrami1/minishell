/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:42:33 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/03 10:46:32 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_env	*ft_lstnew(char *key, char *value)
{
	t_env	*list;
	char *join;
	
	list = malloc(sizeof(t_env));
	if (!list)
		return (NULL);
	list->env_key = key;
	list->env_value = value;
	join = ft_strjoin(list->env_key, "=");
	join = ft_strjoin(join, list->env_value);
	list->line = join;
    list->next = NULL;
	return (list);
}
