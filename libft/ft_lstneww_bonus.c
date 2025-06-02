/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstneww_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:55:13 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/02 13:58:23 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_env	*ft_lstneww(char *key, char *value)
{
	t_env	*list;

	list = malloc(sizeof(t_env));
	if (!list)
		return (NULL);
	list->env_key = key;
	list->env_value = value;
    list->next = NULL;
	return (list);
}